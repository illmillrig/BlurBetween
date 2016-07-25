#pragma once

#include <QtCore/QPointer>
#include <QtGui/QWidget>
#include <QtGui/QSpinBox>

#include "blurBetween_ui.h"

#include <maya/MPxCommand.h>
#include <maya/MArgList.h>



// /usr/autodesk/maya2016.5/bin/uic -o BlurBetween/blurBetween_ui.h blurBetween.ui


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
    Q_OBJECT
public:
    BlurTweenUI( QWidget *parent=0 );
    virtual ~BlurTweenUI();
    virtual void setDefaults();

public slots:
    void openUndoChunk() const;
    void closeUndoChunk() const;

private:
    void createConnections();
    void createCustomWidgets();
    void getTweenType();

private:
    QPointer<BlurSpin> uiTweenSPN;
    QPointer<QPushButton> uiTweenBTN;
    short tweenType = 0;
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


