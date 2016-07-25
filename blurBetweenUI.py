import os
from functools import partial

from PySide import QtCore, QtGui
import pysideuic
import shiboken
import xml.etree.ElementTree as xml
from cStringIO import StringIO

import maya.cmds as cmds
import maya.OpenMaya as om
import maya.OpenMayaAnim as oma
import maya.OpenMayaUI as mui

import random




def getMayaWindow():
	ptr = mui.MQtUtil.mainWindow()
	return shiboken.wrapInstance(long(ptr), QtGui.QMainWindow)


def loadUiType(uiFile):	
	parsed = xml.parse(uiFile)
	widget_class = parsed.find('widget').get('class')
	form_class = parsed.find('class').text
 
	with open(uiFile, 'r') as f:
		o = StringIO()
		frame = {}
 
		pysideuic.compileUi(f, o, indent=0)
		pyc = compile(o.getvalue(), '<string>', 'exec')
		exec pyc in frame
 
		form_class = frame['Ui_%s'%form_class]
		base_class = eval('QtGui.%s'%widget_class)
 
	return form_class, base_class


#-------------------------------------------------------------------------------

hue = random.randrange(0, 360)
color = QtGui.QColor()
color.setHsv(hue, 100, 140)
rgb = color.getRgb()
rgbBright = color.lighter().getRgb()
rgbDark = color.darker().getRgb()

style = r'''
		QPushButton{{
			background-color: rgb{0};
			border-style: solid;
			border-width:0px;
			border-color: rgb(60, 60, 60);
			border-radius:5px;
			color: rgb(40, 40, 40);
			font: 7pt "Tahoma";
		}}

		QPushButton:pressed{{
			background-color: rgb{1};
		}}


		QSlider:groove{{
			background-color: rgb{0};
			border-radius:5px;
		}}

		QSlider:handle:horizontal{{
			width: 3px;
			background-color: rgb{1};
		}}

		QSlider:sub-page:horizontal{{
			background-color: rgb{0};
			border-top-left-radius:5px;
			border-bottom-left-radius:5px;
		}}


		QSlider:add-page:horizontal{{
			border-top-right-radius:5px;
			border-bottom-right-radius:5px;
			background-color: rgb{2};
		}}

		QSpinBox{{

			color: rgb(50, 50, 50);
			background-color: rgb(165, 165, 165);
		}}

		QGroupBox{{
			color: rgb(200, 225, 136);
		}}
		'''.format( rgb, rgbBright, rgbDark )


pwd = os.path.dirname(__file__)
uiName = "blurBetween.ui"
uiFile = os.path.join(pwd, uiName)
form_class, base_class = loadUiType(uiFile)
#-------------------------------------------------------------------------------


class BlurBetweenUI(form_class, base_class):

	def __init__(self, parent=getMayaWindow()):
		super(BlurBetweenUI, self).__init__(parent)
		
		self._checkPlugin()
		
		self.setupUi(self)
		self._createCustomWidgets()
		self.uiTweenSLDR.setRange(-51,151)
		self.setFixedSize(self.sizeHint())

		self.initConnections()
		self.setStyleSheet(style)

		self.tweenType = 0
		self._tweenType()

	#-------------------------------------------------------------------------------
	
	def _checkPlugin(self):
		if not cmds.pluginInfo("BlurBetween", query=True, loaded=True ):
			try:
				cmds.loadPlugin("BlurBetween")
			except:
				raise RuntimeError("Plugin: 'BlurBetween' not found, or cannot be loaded")
		
	#-------------------------------------------------------------------------------
	
	def _createCustomWidgets(self):

		self.uiTweenSPN = SpinBox()
		self.uiTweenSPN.setMinimumWidth(50)
		self.uiTweenSPN.setValue(50)
		self.uiTweenSPN.setMinimum(-100)
		self.uiTweenSPN.setMaximum(200)
		self.uiTweenSPN.setSizePolicy(QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Expanding)

		self.uiTweenBTN = QtGui.QPushButton()
		self.uiTweenBTN.setText("Tween")
		self.uiTweenBTN.setSizePolicy(QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Expanding)
		self.uiTweenBTN.setMinimumHeight(20)
		
		self.tweenWidget.layout().addWidget(self.uiTweenSPN, 0, 0)
		self.tweenWidget.layout().addWidget(self.uiTweenBTN, 1, 0)

	#-------------------------------------------------------------------------------

	def initConnections(self):
		
		# Undo Chunks	
		self.uiTweenSLDR.sliderPressed.connect(lambda: cmds.undoInfo(openChunk=True, chunkName="blurTween"))
		self.uiTweenSLDR.sliderReleased.connect(lambda: cmds.undoInfo(closeChunk=True, chunkName="blurTween"))
		
		# Slider
		self.uiTweenSLDR.sliderPressed.connect(lambda: self.on_clicked(self.uiTweenSLDR.value()))
		self.uiTweenSLDR.sliderPressed.connect(lambda: self.uiTweenSPN.setValue(self.uiTweenSLDR.value()))
		self.uiTweenSLDR.sliderMoved.connect(lambda: self.on_slide(self.uiTweenSLDR.value()))
		self.uiTweenSLDR.sliderMoved.connect(lambda: self.uiTweenSPN.setValue(self.uiTweenSLDR.value()))

		# Spin
		self.uiTweenSPN.stepped.connect(lambda: self.uiTweenSLDR.setValue(self.uiTweenSPN.value()))
		self.uiTweenSPN.stepped.connect(lambda: self.on_clicked(self.uiTweenSPN.value()))
		self.uiTweenSPN.editingFinished.connect(lambda: self.on_clicked(self.uiTweenSPN.value()))
		self.uiTweenSPN.editingFinished.connect(lambda: self.uiTweenSLDR.setValue(self.uiTweenSPN.value()))

		# Tween Btn
		self.uiTweenBTN.clicked.connect(lambda: self.on_clicked(self.uiTweenSPN.value()))

		# Tween Preset BTNs
		for btn in self.seekButtons.findChildren(QtGui.QPushButton):
			btn.clicked.connect(partial(self.uiTweenSPN.setValue, btn.property("mixValue")))
			btn.clicked.connect(partial(self.uiTweenSLDR.setValue, btn.property("mixValue")))
			btn.clicked.connect(partial(self.on_clicked,btn.property("mixValue")))
		
	#-------------------------------------------------------------------------------	
	
	def _tweenType(self):
		if self.uiKeyedCHK.isChecked():
			self.tweenType = 0
		
		elif self.uiMarkedCHK.isChecked():
			self.tweenType = 1
		
		elif self.uiManipulatorCHK.isChecked():
			self.tweenType = 2
		
		elif self.uiCharacterCHK.isChecked():
			self.tweenType = 3
		
		elif self.uiGraphCHK.isChecked():
			self.tweenType = 4

		else:
			self.tweenType = 0

	#-------------------------------------------------------------------------------	
	
	def on_clicked(self, mix):
		self._tweenType()
		cmds.blurTween(mix, self.tweenType, True)

	#-------------------------------------------------------------------------------

	def on_slide(self, mix):	
		cmds.blurTween(mix, self.tweenType, False) # This should be false for sliding

	#-------------------------------------------------------------------------------

def run():
	global _blurBetweenUI
	try:
		_blurBetweenUI.close()
		_blurBetweenUI.deleteLater()
	except: pass
	_blurBetweenUI = BlurBetweenUI()
	_blurBetweenUI.show()

#---------------------------------------------------------------

class SpinBox(QtGui.QSpinBox):
	
	stepped = QtCore.Signal()

	def __init__(self):
		super(SpinBox, self).__init__()

	def stepBy(self, *args):
		super(SpinBox, self).stepBy(*args)
		self.stepped.emit()

#---------------------------------------------------------------


#---------------------------------------------------------------







#---------------------------------------------------------------



