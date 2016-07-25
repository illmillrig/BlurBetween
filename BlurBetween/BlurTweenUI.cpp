
#include "BlurTweenUI.h"

#include <maya/MGlobal.h>


//--------------------------------------------------------------------------------
// CUSTOM WIDGETS
//--------------------------------------------------------------------------------

BlurSpin::BlurSpin(QWidget *parent) : QSpinBox(parent) {

}

void BlurSpin::stepBy(int steps) {
    QSpinBox::stepBy(steps);
    emit this->stepped(steps);
}


//--------------------------------------------------------------------------------
// BLURTWEEN UI
//--------------------------------------------------------------------------------

BlurTweenUI::BlurTweenUI(QWidget *parent) : QWidget(parent) {
    setupUi(this);
    this->createCustomWidgets();
    this->createConnections();
    this->setDefaults();
    this->show();
}

BlurTweenUI::~BlurTweenUI() { }


void BlurTweenUI::setDefaults() {
    this->setFixedSize(this->sizeHint());
    this->uiTweenSLDR->setRange(-51,151);
    this->getTweenType();
}


void BlurTweenUI::createConnections() {
    this->connect(this->uiTweenSLDR, SIGNAL( sliderPressed() ), SLOT( openUndoChunk() ));
    this->connect(this->uiTweenSLDR, SIGNAL( sliderReleased() ), SLOT( closeUndoChunk() ));
}


void BlurTweenUI::openUndoChunk() const {
    MGlobal::executeCommand("undoInfo -chunkName blurTweenUndo -openChunk;");
}


void BlurTweenUI::closeUndoChunk() const {
    MGlobal::executeCommand("undoInfo -chunkName blurTweenUndo -closeChunk;");
}


void BlurTweenUI::createCustomWidgets() {

    this->uiTweenSPN = new BlurSpin(this);
    this->uiTweenSPN->setMinimumWidth(50);
    this->uiTweenSPN->setValue(50);
    this->uiTweenSPN->setMinimum(-100);
    this->uiTweenSPN->setMaximum(200);
    this->uiTweenSPN->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->uiTweenBTN = new QPushButton(this);
    this->uiTweenBTN->setText("Tween");
    this->uiTweenBTN->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->uiTweenBTN->setMinimumHeight(20);

    QLayout *tweenLay = this->tweenWidget->layout();
    tweenLay->addWidget(this->uiTweenSPN);
    tweenLay->addWidget(this->uiTweenBTN);
}


void BlurTweenUI::getTweenType() {

    if (this->uiKeyedCHK->isChecked())
        this->tweenType = 0;

    else if (this->uiMarkedCHK->isChecked())
        this->tweenType = 1;

    else if (this->uiManipulatorCHK->isChecked())
        this->tweenType = 2;

    else if (this->uiCharacterCHK->isChecked())
        this->tweenType = 3;

    else if (this->uiGraphCHK->isChecked())
        this->tweenType = 4;

    else
        this->tweenType = 0;
}


//--------------------------------------------------------------------------------
// BLURTWEEN UI COMMAND
//--------------------------------------------------------------------------------

QPointer<BlurTweenUI>  BlurTweenUICmd::blurTweenWindow;


void* BlurTweenUICmd::creator() {
    return new BlurTweenUICmd;
}


void BlurTweenUICmd::cleanup(){
    if (blurTweenWindow != nullptr)
        delete blurTweenWindow;
}


MStatus BlurTweenUICmd::doIt(const MArgList &args ){

    if (blurTweenWindow == nullptr){
        blurTweenWindow = new BlurTweenUI();
    }

    else {
        blurTweenWindow->showNormal();
        blurTweenWindow->raise();
    }

    return MS::kSuccess;
}

