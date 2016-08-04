#pragma once

#include <QtCore/QPointer>
#include <QtGui/QWidget>
#include <QtGui/QSpinBox>


// TODO: Figure how to save the output of AUTOUI into src dir
#include "ui_BlurBetween.h"



#include "Tweener.h"
#include <maya/MPxCommand.h>
#include <maya/MArgList.h>
#include <maya/MMessage.h>

#include <QtGui/QPushButton>


//--------------------------------------------------------------------------------
// CUSTOM WIDGETS
//--------------------------------------------------------------------------------


class BlurSpin : public QSpinBox {
    Q_OBJECT
public:
    BlurSpin(QWidget *parent=0);
signals:
    void stepped(int steps);

public slots:
    void stepBy(int steps);
};


//--------------------------------------------------------------------------------
// EVENT FILTERS
//--------------------------------------------------------------------------------

class ViewRefreshFilter : public QObject {
    Q_OBJECT
public:
    ViewRefreshFilter();
    virtual bool eventFilter(QObject *obj, QEvent *event);
};


//--------------------------------------------------------------------------------
// BLURTWEEN UI
//--------------------------------------------------------------------------------

class BlurBetweenUI : public QWidget, private Ui::BlurTween{
    Q_OBJECT
public:
    BlurBetweenUI( QWidget *parent=0 );
    virtual ~BlurBetweenUI();
    virtual void setDefaults();
    void moveToPosition();

public slots:
    void openUndoChunk() const;
    void closeUndoChunk() const;
    void onClicked();
    void onSliderClicked();
    void onSeek();
    void onSlide();
    void onSlide(const int &mix);
    void onRelease();
    void onRelease(const int &mix);
    void quickTween(const int &mix, const bool &fresh);
    void fullTween(const int &mix, const bool &fresh);
    void setSliderValue();
    void setSliderValue(const int &mix);
    void setSpinValue();
    void setSpinValue(const int &mix);
    void setSliderValueFromSeek();
    void setSpinValueFromSeek();


private:
    void createConnections();
    void createEventFilters();
    void destroyEventFilters();
    void createCustomWidgets();
    void setTweenType();
    MCallbackId callbackID;
    ViewRefreshFilter *freshFilter;

private:
    QPointer<BlurSpin> uiTweenSPN;
    QPointer<QPushButton> uiTweenBTN;
    short tweenType = 0;
    MAnimCurveChange nullAnimCurveChange;
};


//--------------------------------------------------------------------------------
// BLURTWEEN UI COMMAND
//--------------------------------------------------------------------------------

class BlurTweenUICmd : public MPxCommand {
public:
    static void *creator();
    static void cleanup();

    MStatus doIt(const MArgList &args);
    bool isUndoable() const { return false; }

public:
    static QPointer<BlurBetweenUI> blurTweenWindow;
};



