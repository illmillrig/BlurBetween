
#include "BlurBetweenUI.h"
#include "BlurBetweenCmd.h"

#include <QtGui/QPushButton>
#include <QtGui/QMainWindow>
#include <QtCore/QList>

#include <maya/MGlobal.h>
#include <maya/MQtUtil.h>
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
// EVENT FILTERS
//--------------------------------------------------------------------------------


ViewRefreshFilter::ViewRefreshFilter() { }

bool ViewRefreshFilter::eventFilter(QObject *obj, QEvent *event){

    if (event->type() == QEvent::Resize)
        BlurTweenUICmd::blurTweenWindow->moveToPosition();

    return false;
}


//--------------------------------------------------------------------------------
// BLURTWEEN UI
//--------------------------------------------------------------------------------

BlurBetweenUI::BlurBetweenUI(QWidget *parent) : QWidget(parent) {
    setupUi(this);
    this->createCustomWidgets();
    this->createConnections();
    this->setDefaults();
    this->moveToPosition();
    this->show();
}


BlurBetweenUI::~BlurBetweenUI() {
    if (this->uiTweenSLDR != nullptr)
        delete this->uiTweenSLDR;

    if (this->uiTweenSPN != nullptr)
        delete this->uiTweenSPN;

    this->destroyEventFilters();

    if (this->freshFilter != nullptr)
        delete this->freshFilter;
}


void BlurBetweenUI::setDefaults() {
    this->setFixedSize(this->sizeHint());
    this->setWindowFlags(Qt::FramelessWindowHint);

    // TODO: Test setting this to false on Windows for a transparent background
    this->setAutoFillBackground(true);

    this->setTweenType();
    this->uiTweenSLDR->setRange(-25,125);
    this->uiTweenSPN->setRange(-25,125);

    this->freshFilter = new ViewRefreshFilter;
    this->createEventFilters();
}


void BlurBetweenUI::createEventFilters() {
    QWidget *mayaWindow = MQtUtil::mainWindow();
    QWidget *viewPanes = mayaWindow->findChild <QWidget*> ("viewPanes");

    viewPanes->installEventFilter(this->freshFilter);
}


void BlurBetweenUI::destroyEventFilters() {
    QWidget *mayaWindow = MQtUtil::mainWindow();
    QWidget *viewPanes = mayaWindow->findChild <QWidget*> ("viewPanes");

    viewPanes->removeEventFilter(this->freshFilter);
}


void BlurBetweenUI::createConnections() {

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


void BlurBetweenUI::createCustomWidgets() {

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


void BlurBetweenUI::openUndoChunk() const {
    MGlobal::executeCommand("undoInfo -chunkName blurTweenUndo -openChunk;");
}


void BlurBetweenUI::closeUndoChunk() const {
    MGlobal::executeCommand("undoInfo -chunkName blurTweenUndo -closeChunk;");
}


// This seems strange I know, but the logic is this:
// we need to make calls through the commands layer with MGlobal::executeCommand("blurTween") so that tweens get added to the undo que.
// But we don't really always need undos.  like while we're sliding.  so we keep a ptr to the static tweener class of the src
// MpxCommand in order for the tweener class to tween with existing information and be fast while sliding.


void BlurBetweenUI::onClicked() {
    this->fullTween(this->uiTweenSPN->value(), true);
}


void BlurBetweenUI::onSliderClicked() {
    this->fullTween(this->uiTweenSLDR->value(), true);
}


void BlurBetweenUI::onSeek() {
    int seekValue = sender()->property("mixValue").toInt();
    this->fullTween(seekValue, true);
}


void BlurBetweenUI::onSlide() {
    int mix = this->uiTweenSLDR->value();
    this->quickTween(mix, false);
}


void BlurBetweenUI::onSlide(const int &mix) {
    this->quickTween(mix, false);
}


void BlurBetweenUI::onRelease() {
    int mix = this->uiTweenSLDR->value();
    this->fullTween(mix, false);
}


void BlurBetweenUI::onRelease(const int &mix) {
    this->fullTween(mix, false);
}


void BlurBetweenUI::quickTween(const int &mix, const bool &fresh) {
    BlurBetween::bTween.tweenAnimPlugs(mix/100.0, this->tweenType, fresh, &this->nullAnimCurveChange);
}


void BlurBetweenUI::fullTween(const int &mix, const bool &fresh) {

   this->setTweenType();

    // TODO: This could probably be cleaned up/optimized a bit :)

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


void BlurBetweenUI::setSliderValue() {
    this->uiTweenSLDR->setValue(this->uiTweenSPN->value());
}


void BlurBetweenUI::setSliderValue(const int &mix) {
    this->uiTweenSLDR->setValue(mix);
}


void BlurBetweenUI::setSpinValue() {
    this->uiTweenSPN->setValue(this->uiTweenSLDR->value());
}


void BlurBetweenUI::setSpinValue(const int &mix) {
    this->uiTweenSPN->setValue(mix);
}


void BlurBetweenUI::setSliderValueFromSeek() {
    int seekValue = sender()->property("mixValue").toInt();
    this->uiTweenSLDR->setValue(seekValue);
}


void BlurBetweenUI::setSpinValueFromSeek() {
    int seekValue = sender()->property("mixValue").toInt();
    this->uiTweenSPN->setValue(seekValue);
}


void BlurBetweenUI::setTweenType() {

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


void BlurBetweenUI::moveToPosition() {
    QWidget *mayaWindow = this->parentWidget();
    QWidget *viewPanes = mayaWindow->findChild <QWidget*> ("viewPanes");

    QRect viewRect = viewPanes->rect();

    QPoint topLeft = viewPanes->mapTo(mayaWindow, viewRect.topLeft());
    QPoint topRight = viewPanes->mapTo(mayaWindow, viewRect.topRight());
    QPoint center = (topLeft + topRight) / 2;

    center.setY(center.y() + (this->height()/2 + 3));
    center.setX(center.x() - (this->width()/2));

    this->move(center);
    this->raise();
}


//--------------------------------------------------------------------------------
// BLURTWEEN UI COMMAND
//--------------------------------------------------------------------------------

QPointer<BlurBetweenUI>  BlurTweenUICmd::blurTweenWindow;

void* BlurTweenUICmd::creator() {
    return new BlurTweenUICmd;
}


void BlurTweenUICmd::cleanup(){
    if (blurTweenWindow != nullptr)
        delete blurTweenWindow;
}


MStatus BlurTweenUICmd::doIt(const MArgList &args ){
    if (blurTweenWindow == nullptr)
        blurTweenWindow = new BlurBetweenUI(MQtUtil::mainWindow());

    else {
        blurTweenWindow->showNormal();
        blurTweenWindow->raise();
    }

    return MS::kSuccess;
}

