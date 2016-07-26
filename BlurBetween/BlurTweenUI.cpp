
#include "BlurTweenUI.h"
#include "BlurBetweenCmd.h"

#include <QtGui/QPushButton>
#include <QtCore/QList>

#include <maya/MGlobal.h>
#include <maya/MAnimCurveChange.h>


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
    this->setTweenType();
}


void BlurTweenUI::createConnections() {
    // Undos
    this->connect(this->uiTweenSLDR, SIGNAL( sliderPressed() ), SLOT( openUndoChunk() ));
    this->connect(this->uiTweenSLDR, SIGNAL( sliderReleased() ), SLOT( closeUndoChunk() ));

    // Slider
    this->connect(this->uiTweenSLDR, SIGNAL( sliderPressed() ), SLOT( [this] () {this->onClicked(this->uiTweenSLDR.value());} ));
    this->connect(this->uiTweenSLDR, SIGNAL( sliderPressed() ), SLOT( [this] () {this->uiTweenSPN->setValue( this->uiTweenSLDR->value() );} ));

    this->connect(this->uiTweenSLDR, SIGNAL( sliderMoved() ), SLOT( [this] () {this->onSlide(this->uiTweenSLDR.value());} ));
    this->connect(this->uiTweenSLDR, SIGNAL( sliderMoved() ), SLOT( [this] () {this->uiTweenSPN->setValue( this->uiTweenSLDR->value() );} ));

    // Spin
    this->connect(this->uiTweenSPN, SIGNAL( stepped() ), SLOT( [this] () {this->uiTweenSLDR->setValue( this->uiTweenSPN->value() );} ));
    this->connect(this->uiTweenSPN, SIGNAL( stepped() ), SLOT( [this] () {this->onClicked(this->uiTweenSPN.value());} ));

    this->connect(this->uiTweenSPN, SIGNAL( editingFinished() ), SLOT( [this] () {this->onClicked(this->uiTweenSPN.value());} ));
    this->connect(this->uiTweenSPN, SIGNAL( editingFinished() ), SLOT( [this] () {this->uiTweenSLDR->setValue( this->uiTweenSPN->value() );} ));

    // Tween Btn
    this->connect(this->uiTweenBTN, SIGNAL( clicked() ), SLOT( [this] () {this->onClicked(this->uiTweenSPN.value());} ));

    // Tween Mix Preset Btns
    const QObjectList children = this->seekButtons->children();
    for (auto btn : children){
        this->connect(btn, SIGNAL( clicked() ), SLOT( [this] () {this->uiTweenSPN->setValue( this->uiTweenSLDR->value() );} ));
        this->connect(btn, SIGNAL( clicked() ), SLOT( [this] () {this->uiTweenSLDR->setValue( this->uiTweenSPN->value() );} ));
        this->connect(btn, SIGNAL( clicked() ), SLOT( [this, btn] () {this->onClicked(btn->property("mixValue"));} ));
    }
}


void BlurTweenUI::openUndoChunk() const {
    MGlobal::executeCommand("undoInfo -chunkName blurTweenUndo -openChunk;");
}


void BlurTweenUI::closeUndoChunk() const {
    MGlobal::executeCommand("undoInfo -chunkName blurTweenUndo -closeChunk;");
}


void BlurTweenUI::onClicked(const int &mix) {

    // UI tweening type
    this->setTweenType();

    // tween without undo
    quickTween(mix, true);
}


void BlurTweenUI::onSlide(const int &mix) {
    // tween without undo
    quickTween(mix, false);
}


void BlurTweenUI::onRelease(const int &mix) {
    // tween with undo
    // MGlobal::executeCommand();
}


void BlurTweenUI::quickTween(const int &mix, const bool &fresh) {
    this->bTweener.tweenAnimPlugs((mix / 100.0), this->tweenType, fresh, &this->nullAnimCurveChange);
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


void BlurTweenUI::setTweenType() {

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

