#pragma once

#include <QtCore/QPointer>
#include <QtGui/QWidget>
#include <QtGui/QSpinBox>

#include "blurBetween_ui.h"
#include "Tweener.h"

#include <maya/MPxCommand.h>
#include <maya/MArgList.h>






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
// BLURTWEEN UI
//--------------------------------------------------------------------------------

class BlurTweenUI : public QWidget, public Ui::BlurTween{
// /usr/autodesk/maya2016.5/bin/uic -o BlurBetween/blurBetween_ui.h blurBetween.ui
    Q_OBJECT
public:
    BlurTweenUI( QWidget *parent=0 );
    virtual ~BlurTweenUI();
    virtual void setDefaults();

public slots:
    void openUndoChunk() const;
    void closeUndoChunk() const;
    void onClicked();
    void onClicked(const int &mix);
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
    void createCustomWidgets();
    void setTweenType();
    void tweenAll(const int &mix, const bool &fresh);

private:
    QPointer<BlurSpin> uiTweenSPN;
    QPointer<QPushButton> uiTweenBTN;
    short tweenType = 0;

    Tweener bTweener;
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
    static QPointer<BlurTweenUI> blurTweenWindow;
};


