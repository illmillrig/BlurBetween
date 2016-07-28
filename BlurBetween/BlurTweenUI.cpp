
#include "BlurTweenUI.h"
#include "BlurBetweenCmd.h"

#include <QtGui/QPushButton>
#include <QtCore/QList>

#include <maya/MGlobal.h>
#include <maya/MAnimCurveChange.h>


//--------------------------------------------------------------------------------
// CUSTOM WIDGETS
//--------------------------------------------------------------------------------

BlurSpin::BlurSpin(QWidget *parent) : QSpinBox(parent) { }

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


BlurTweenUI::~BlurTweenUI() {
    if (this->uiTweenSLDR != nullptr)
        delete this->uiTweenSLDR;

    if (this->uiTweenSPN != nullptr)
        delete this->uiTweenSPN;
}


void BlurTweenUI::setDefaults() {
    this->setFixedSize(this->sizeHint());
    this->uiTweenSLDR->setRange(-51,151);
    this->setTweenType();
//    this->setWindowFlags(Qt::FramelessWindowHint);
}


void BlurTweenUI::createConnections() {

    // Undos
    this->connect(this->uiTweenSLDR, SIGNAL( sliderPressed() ), SLOT( openUndoChunk() ));
    this->connect(this->uiTweenSLDR, SIGNAL( sliderReleased() ), SLOT( closeUndoChunk() ));

    // Slider
    this->connect(this->uiTweenSLDR, SIGNAL( sliderPressed() ), SLOT( onSliderClicked() ));
    this->connect(this->uiTweenSLDR, SIGNAL( sliderPressed() ), SLOT( setSpinValue() ));
    this->connect(this->uiTweenSLDR, SIGNAL( sliderMoved(int) ), SLOT( onSlide(int) ));
    this->connect(this->uiTweenSLDR, SIGNAL( sliderMoved(int) ), SLOT( setSpinValue(int) ));

    // Spin
    this->connect(this->uiTweenSPN, SIGNAL( stepped(int) ), SLOT( setSliderValue() ));
    this->connect(this->uiTweenSPN, SIGNAL( stepped(int) ), SLOT( onClicked() ));
    this->connect(this->uiTweenSPN, SIGNAL( editingFinished() ), SLOT( onClicked() ));
    this->connect(this->uiTweenSPN, SIGNAL( editingFinished() ), SLOT( setSliderValue() ));

    // Tween Btn
    this->connect(this->uiTweenBTN, SIGNAL( clicked(bool) ), SLOT( onClicked() ));

    // Tween Mix Preset Btns
    const QList <QPushButton*> seekBtns = this->seekButtons->findChildren <QPushButton*> ();
    for (const auto btn : seekBtns){
        this->connect(btn, SIGNAL( clicked(bool) ), SLOT( setSpinValueFromSeek() ));
        this->connect(btn, SIGNAL( clicked(bool) ), SLOT( setSliderValueFromSeek() ));
        this->connect(btn, SIGNAL( clicked(bool) ), SLOT( onSeek() ));
    }
}


void BlurTweenUI::createCustomWidgets() {

    this->uiTweenSPN = new BlurSpin(this);
    this->uiTweenSPN->setMinimumWidth(50);
    this->uiTweenSPN->setValue(50);
    this->uiTweenSPN->setMinimum(-100);
    this->uiTweenSPN->setMaximum(200);
    this->uiTweenSPN->setFocusPolicy(Qt::ClickFocus);
    this->uiTweenSPN->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->uiTweenBTN = new QPushButton(this);
    this->uiTweenBTN->setText("Tween");
    this->uiTweenBTN->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->uiTweenBTN->setMinimumHeight(20);

    QLayout *tweenLay = this->tweenWidget->layout();
    tweenLay->addWidget(this->uiTweenSPN);
    tweenLay->addWidget(this->uiTweenBTN);
}


void BlurTweenUI::openUndoChunk() const {
    MGlobal::executeCommand("undoInfo -chunkName blurTweenUndo -openChunk;");
}


void BlurTweenUI::closeUndoChunk() const {
    MGlobal::executeCommand("undoInfo -chunkName blurTweenUndo -closeChunk;");
}


// This seems strange I know, but the logic is this:
// we need to make calls through the commands layer with MGlobal::executeCommand("blurTween") so that tweens get added to the undo que. But we don't
// really always need undos.  like while we're sliding.  However, In order for the tweener class to tween with existing information and be
// fast (refresh=false), we would need to have already tweened with it set (refresh=true).  That's why when the slider is pressed,
// we quickTween and fullTween. fullTween so we can undo back to before this, and quickTween so that while after clicking, while we're
// sliding, we can just tween only with no undo information and bypass calls through the commands layer.  when we release, we fullTween
// once more to get undo's added to the que.
// Also, no having lambda expressions for signal slot connections in 4.8 requires a few more convenience functions for passing around values


void BlurTweenUI::onClicked() {
    this->fullTween(this->uiTweenSPN->value(), true);
}


void BlurTweenUI::onSliderClicked() {
    this->tweenAll(this->uiTweenSLDR->value(), true);
}


void BlurTweenUI::onSeek() {
    int seekValue = sender()->property("mixValue").toInt();
    this->tweenAll(seekValue, true);
}


void BlurTweenUI::tweenAll(const int &mix, const bool &fresh) {
    this->setTweenType();

    // full tween once so we can undo to before this
    this->fullTween(mix, true);

    // quick tween once to set tween class data for use while sliding - much faster
    this->quickTween(mix, true);
}


void BlurTweenUI::onSlide() {
    int mix = this->uiTweenSLDR->value();
    this->quickTween(mix, false);
}


void BlurTweenUI::onSlide(const int &mix) {
    this->quickTween(mix, false);
}


void BlurTweenUI::onRelease() {
    int mix = this->uiTweenSLDR->value();
    this->fullTween(mix, false);
}


void BlurTweenUI::onRelease(const int &mix) {
    this->fullTween(mix, false);
}


void BlurTweenUI::quickTween(const int &mix, const bool &fresh) {
    this->bTweener.tweenAnimPlugs((mix / 100.0), this->tweenType, fresh, &this->nullAnimCurveChange);
}


void BlurTweenUI::fullTween(const int &mix, const bool &fresh) {

    // TODO: This could probably be cleaned up/optimized a bit.

    MString cmd ("blurTween");

    MString ttype;
    ttype.set(this->tweenType);

    MString mmix;
    mmix.set(mix);

    MString refresh;
    refresh.set(true);

    cmd += " " +  mmix + " " + ttype + " " + refresh;

    MStatus stat;
    stat = MGlobal::executeCommand(cmd, false, true);
    CHECK_MSTATUS(stat);
}


void BlurTweenUI::setSliderValue() {
    this->uiTweenSLDR->setValue(this->uiTweenSPN->value());
}


void BlurTweenUI::setSliderValue(const int &mix) {
    this->uiTweenSLDR->setValue(mix);
}


void BlurTweenUI::setSpinValue() {
    this->uiTweenSPN->setValue(this->uiTweenSLDR->value());
}


void BlurTweenUI::setSpinValue(const int &mix) {
    this->uiTweenSPN->setValue(mix);
}


void BlurTweenUI::setSliderValueFromSeek() {
    int seekValue = sender()->property("mixValue").toInt();
    this->uiTweenSLDR->setValue(seekValue);
}


void BlurTweenUI::setSpinValueFromSeek() {
    int seekValue = sender()->property("mixValue").toInt();
    this->uiTweenSPN->setValue(seekValue);
}


void BlurTweenUI::setTweenType() {

    if (this->uiKeyedCHK->isChecked()){
        this->tweenType = 0;
        return;
    }

    else if (this->uiMarkedCHK->isChecked()){
        this->tweenType = 1;
        return;
    }

    else if (this->uiManipulatorCHK->isChecked()){
        this->tweenType = 2;
        return;
    }

    else if (this->uiCharacterCHK->isChecked()){
        this->tweenType = 3;
        return;
    }

    else if (this->uiGraphCHK->isChecked()){
        this->tweenType = 4;
        return;
    }

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

    if (blurTweenWindow == nullptr)
        blurTweenWindow = new BlurTweenUI();

    else {
        blurTweenWindow->showNormal();
        blurTweenWindow->raise();
    }

    return MS::kSuccess;
}

