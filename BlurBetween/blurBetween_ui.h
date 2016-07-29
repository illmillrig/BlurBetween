/********************************************************************************
** Form generated from reading UI file 'blurBetween.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef BLURBETWEEN_UI_H
#define BLURBETWEEN_UI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BlurTween
{
public:
    QGridLayout *gridLayout;
    QWidget *uiBreakdownGRP;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_23;
    QWidget *tweenWidget;
    QGridLayout *gridLayout_4;
    QWidget *tweenSeekLayout;
    QGridLayout *gridLayout_5;
    QWidget *seekButtons;
    QGridLayout *gridLayout_6;
    QPushButton *uiSeek0BTN_2;
    QPushButton *uiSeek25BTN;
    QPushButton *uiSeek100BTN;
    QPushButton *uiSeek50BTN;
    QPushButton *uiSeek75BTN;
    QPushButton *uiSeek75BTN_2;
    QPushButton *uiSeek25BTN_2;
    QPushButton *uiSeek25BTN_3;
    QPushButton *uiSeek75BTN_3;
    QPushButton *uiSeek75BTN_4;
    QPushButton *uiSeek75BTN_5;
    QSlider *uiTweenSLDR;
    QWidget *uiTweenTypeWidget;
    QGridLayout *gridLayout_2;
    QCheckBox *uiKeyedCHK;
    QCheckBox *uiMarkedCHK;
    QCheckBox *uiManipulatorCHK;
    QCheckBox *uiCharacterCHK;
    QCheckBox *uiGraphCHK;

    void setupUi(QWidget *BlurTween)
    {
        if (BlurTween->objectName().isEmpty())
            BlurTween->setObjectName(QString::fromUtf8("BlurTween"));
        BlurTween->resize(376, 88);
        BlurTween->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QPushButton{\n"
"	background-color: rgb(89, 113, 147);\n"
"	border-style: solid;\n"
"	border-width:0px;\n"
"	border-color: rgb(60, 60, 60);\n"
"	border-radius:5px;\n"
"	color: rgb(40, 40, 40);\n"
"	font: 7pt \"Tahoma\";\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: rgb(107, 136, 177);\n"
"}\n"
"\n"
"\n"
"QSlider:groove{\n"
"	background-color: rgb(89, 113, 147);\n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QSlider:handle:horizontal{\n"
"	width: 3px;\n"
"	background-color: rgb(107, 136, 177);\n"
"}\n"
"\n"
"QSlider:sub-page:horizontal{		\n"
"	background-color: rgb(89, 113, 147);\n"
"	border-top-left-radius:5px;\n"
"	border-bottom-left-radius:5px;\n"
"}\n"
"\n"
"\n"
"QSlider:add-page:horizontal{		\n"
"	border-top-right-radius:5px;\n"
"	border-bottom-right-radius:5px;\n"
"	background-color: rgb(70, 90, 117);\n"
"}\n"
"\n"
"QSpinBox{	\n"
"	color: rgb(50, 50, 50);\n"
"	background-color: rgb(165, 165, 165);\n"
"}\n"
"\n"
"QGroupBox{\n"
"	color: rgb(200, 225, 136);\n"
"}"));
        gridLayout = new QGridLayout(BlurTween);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(2, 2, 2, 2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        uiBreakdownGRP = new QWidget(BlurTween);
        uiBreakdownGRP->setObjectName(QString::fromUtf8("uiBreakdownGRP"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(uiBreakdownGRP->sizePolicy().hasHeightForWidth());
        uiBreakdownGRP->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(uiBreakdownGRP);
        gridLayout_3->setSpacing(4);
        gridLayout_3->setContentsMargins(2, 2, 2, 2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        tweenWidget = new QWidget(uiBreakdownGRP);
        tweenWidget->setObjectName(QString::fromUtf8("tweenWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tweenWidget->sizePolicy().hasHeightForWidth());
        tweenWidget->setSizePolicy(sizePolicy1);
        gridLayout_4 = new QGridLayout(tweenWidget);
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(2);
        gridLayout_4->setVerticalSpacing(4);

        horizontalLayout_23->addWidget(tweenWidget);

        tweenSeekLayout = new QWidget(uiBreakdownGRP);
        tweenSeekLayout->setObjectName(QString::fromUtf8("tweenSeekLayout"));
        gridLayout_5 = new QGridLayout(tweenSeekLayout);
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setHorizontalSpacing(2);
        gridLayout_5->setVerticalSpacing(4);
        seekButtons = new QWidget(tweenSeekLayout);
        seekButtons->setObjectName(QString::fromUtf8("seekButtons"));
        gridLayout_6 = new QGridLayout(seekButtons);
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setHorizontalSpacing(4);
        gridLayout_6->setVerticalSpacing(0);
        uiSeek0BTN_2 = new QPushButton(seekButtons);
        uiSeek0BTN_2->setObjectName(QString::fromUtf8("uiSeek0BTN_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(uiSeek0BTN_2->sizePolicy().hasHeightForWidth());
        uiSeek0BTN_2->setSizePolicy(sizePolicy2);
        uiSeek0BTN_2->setMinimumSize(QSize(0, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        font.setPointSize(7);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        uiSeek0BTN_2->setFont(font);
        uiSeek0BTN_2->setProperty("mixValue", QVariant(0));

        gridLayout_6->addWidget(uiSeek0BTN_2, 0, 0, 1, 1);

        uiSeek25BTN = new QPushButton(seekButtons);
        uiSeek25BTN->setObjectName(QString::fromUtf8("uiSeek25BTN"));
        sizePolicy2.setHeightForWidth(uiSeek25BTN->sizePolicy().hasHeightForWidth());
        uiSeek25BTN->setSizePolicy(sizePolicy2);
        uiSeek25BTN->setMinimumSize(QSize(0, 20));
        uiSeek25BTN->setFont(font);
        uiSeek25BTN->setProperty("mixValue", QVariant(20));

        gridLayout_6->addWidget(uiSeek25BTN, 0, 2, 1, 1);

        uiSeek100BTN = new QPushButton(seekButtons);
        uiSeek100BTN->setObjectName(QString::fromUtf8("uiSeek100BTN"));
        sizePolicy2.setHeightForWidth(uiSeek100BTN->sizePolicy().hasHeightForWidth());
        uiSeek100BTN->setSizePolicy(sizePolicy2);
        uiSeek100BTN->setMinimumSize(QSize(0, 20));
        uiSeek100BTN->setFont(font);
        uiSeek100BTN->setProperty("mixValue", QVariant(100));

        gridLayout_6->addWidget(uiSeek100BTN, 0, 10, 1, 1);

        uiSeek50BTN = new QPushButton(seekButtons);
        uiSeek50BTN->setObjectName(QString::fromUtf8("uiSeek50BTN"));
        sizePolicy2.setHeightForWidth(uiSeek50BTN->sizePolicy().hasHeightForWidth());
        uiSeek50BTN->setSizePolicy(sizePolicy2);
        uiSeek50BTN->setMinimumSize(QSize(0, 20));
        uiSeek50BTN->setFont(font);
        uiSeek50BTN->setProperty("mixValue", QVariant(40));

        gridLayout_6->addWidget(uiSeek50BTN, 0, 4, 1, 1);

        uiSeek75BTN = new QPushButton(seekButtons);
        uiSeek75BTN->setObjectName(QString::fromUtf8("uiSeek75BTN"));
        sizePolicy2.setHeightForWidth(uiSeek75BTN->sizePolicy().hasHeightForWidth());
        uiSeek75BTN->setSizePolicy(sizePolicy2);
        uiSeek75BTN->setMinimumSize(QSize(0, 20));
        uiSeek75BTN->setFont(font);
        uiSeek75BTN->setProperty("mixValue", QVariant(60));

        gridLayout_6->addWidget(uiSeek75BTN, 0, 6, 1, 1);

        uiSeek75BTN_2 = new QPushButton(seekButtons);
        uiSeek75BTN_2->setObjectName(QString::fromUtf8("uiSeek75BTN_2"));
        sizePolicy2.setHeightForWidth(uiSeek75BTN_2->sizePolicy().hasHeightForWidth());
        uiSeek75BTN_2->setSizePolicy(sizePolicy2);
        uiSeek75BTN_2->setMinimumSize(QSize(0, 20));
        uiSeek75BTN_2->setFont(font);
        uiSeek75BTN_2->setProperty("mixValue", QVariant(50));

        gridLayout_6->addWidget(uiSeek75BTN_2, 0, 5, 1, 1);

        uiSeek25BTN_2 = new QPushButton(seekButtons);
        uiSeek25BTN_2->setObjectName(QString::fromUtf8("uiSeek25BTN_2"));
        sizePolicy2.setHeightForWidth(uiSeek25BTN_2->sizePolicy().hasHeightForWidth());
        uiSeek25BTN_2->setSizePolicy(sizePolicy2);
        uiSeek25BTN_2->setMinimumSize(QSize(0, 20));
        uiSeek25BTN_2->setFont(font);
        uiSeek25BTN_2->setProperty("mixValue", QVariant(30));

        gridLayout_6->addWidget(uiSeek25BTN_2, 0, 3, 1, 1);

        uiSeek25BTN_3 = new QPushButton(seekButtons);
        uiSeek25BTN_3->setObjectName(QString::fromUtf8("uiSeek25BTN_3"));
        sizePolicy2.setHeightForWidth(uiSeek25BTN_3->sizePolicy().hasHeightForWidth());
        uiSeek25BTN_3->setSizePolicy(sizePolicy2);
        uiSeek25BTN_3->setMinimumSize(QSize(0, 20));
        uiSeek25BTN_3->setFont(font);
        uiSeek25BTN_3->setProperty("mixValue", QVariant(10));

        gridLayout_6->addWidget(uiSeek25BTN_3, 0, 1, 1, 1);

        uiSeek75BTN_3 = new QPushButton(seekButtons);
        uiSeek75BTN_3->setObjectName(QString::fromUtf8("uiSeek75BTN_3"));
        sizePolicy2.setHeightForWidth(uiSeek75BTN_3->sizePolicy().hasHeightForWidth());
        uiSeek75BTN_3->setSizePolicy(sizePolicy2);
        uiSeek75BTN_3->setMinimumSize(QSize(0, 20));
        uiSeek75BTN_3->setFont(font);
        uiSeek75BTN_3->setProperty("mixValue", QVariant(70));

        gridLayout_6->addWidget(uiSeek75BTN_3, 0, 7, 1, 1);

        uiSeek75BTN_4 = new QPushButton(seekButtons);
        uiSeek75BTN_4->setObjectName(QString::fromUtf8("uiSeek75BTN_4"));
        sizePolicy2.setHeightForWidth(uiSeek75BTN_4->sizePolicy().hasHeightForWidth());
        uiSeek75BTN_4->setSizePolicy(sizePolicy2);
        uiSeek75BTN_4->setMinimumSize(QSize(0, 20));
        uiSeek75BTN_4->setFont(font);
        uiSeek75BTN_4->setProperty("mixValue", QVariant(80));

        gridLayout_6->addWidget(uiSeek75BTN_4, 0, 8, 1, 1);

        uiSeek75BTN_5 = new QPushButton(seekButtons);
        uiSeek75BTN_5->setObjectName(QString::fromUtf8("uiSeek75BTN_5"));
        sizePolicy2.setHeightForWidth(uiSeek75BTN_5->sizePolicy().hasHeightForWidth());
        uiSeek75BTN_5->setSizePolicy(sizePolicy2);
        uiSeek75BTN_5->setMinimumSize(QSize(0, 20));
        uiSeek75BTN_5->setFont(font);
        uiSeek75BTN_5->setProperty("mixValue", QVariant(90));

        gridLayout_6->addWidget(uiSeek75BTN_5, 0, 9, 1, 1);


        gridLayout_5->addWidget(seekButtons, 1, 0, 1, 1);

        uiTweenSLDR = new QSlider(tweenSeekLayout);
        uiTweenSLDR->setObjectName(QString::fromUtf8("uiTweenSLDR"));
        sizePolicy2.setHeightForWidth(uiTweenSLDR->sizePolicy().hasHeightForWidth());
        uiTweenSLDR->setSizePolicy(sizePolicy2);
        uiTweenSLDR->setMinimum(-50);
        uiTweenSLDR->setMaximum(150);
        uiTweenSLDR->setValue(50);
        uiTweenSLDR->setTracking(true);
        uiTweenSLDR->setOrientation(Qt::Horizontal);
        uiTweenSLDR->setInvertedAppearance(false);
        uiTweenSLDR->setInvertedControls(true);
        uiTweenSLDR->setTickPosition(QSlider::NoTicks);
        uiTweenSLDR->setTickInterval(5);

        gridLayout_5->addWidget(uiTweenSLDR, 0, 0, 1, 1);


        horizontalLayout_23->addWidget(tweenSeekLayout);


        gridLayout_3->addLayout(horizontalLayout_23, 1, 0, 1, 1);

        uiTweenTypeWidget = new QWidget(uiBreakdownGRP);
        uiTweenTypeWidget->setObjectName(QString::fromUtf8("uiTweenTypeWidget"));
        gridLayout_2 = new QGridLayout(uiTweenTypeWidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        uiKeyedCHK = new QCheckBox(uiTweenTypeWidget);
        uiKeyedCHK->setObjectName(QString::fromUtf8("uiKeyedCHK"));
        uiKeyedCHK->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(uiKeyedCHK->sizePolicy().hasHeightForWidth());
        uiKeyedCHK->setSizePolicy(sizePolicy3);
        QFont font1;
        font1.setPointSize(8);
        uiKeyedCHK->setFont(font1);
        uiKeyedCHK->setFocusPolicy(Qt::StrongFocus);
        uiKeyedCHK->setAutoFillBackground(false);
        uiKeyedCHK->setChecked(true);
        uiKeyedCHK->setAutoExclusive(true);

        gridLayout_2->addWidget(uiKeyedCHK, 0, 0, 1, 1);

        uiMarkedCHK = new QCheckBox(uiTweenTypeWidget);
        uiMarkedCHK->setObjectName(QString::fromUtf8("uiMarkedCHK"));
        uiMarkedCHK->setEnabled(true);
        sizePolicy3.setHeightForWidth(uiMarkedCHK->sizePolicy().hasHeightForWidth());
        uiMarkedCHK->setSizePolicy(sizePolicy3);
        uiMarkedCHK->setFont(font1);
        uiMarkedCHK->setFocusPolicy(Qt::StrongFocus);
        uiMarkedCHK->setAutoFillBackground(false);
        uiMarkedCHK->setAutoExclusive(true);

        gridLayout_2->addWidget(uiMarkedCHK, 0, 1, 1, 1);

        uiManipulatorCHK = new QCheckBox(uiTweenTypeWidget);
        uiManipulatorCHK->setObjectName(QString::fromUtf8("uiManipulatorCHK"));
        uiManipulatorCHK->setEnabled(true);
        sizePolicy3.setHeightForWidth(uiManipulatorCHK->sizePolicy().hasHeightForWidth());
        uiManipulatorCHK->setSizePolicy(sizePolicy3);
        uiManipulatorCHK->setFont(font1);
        uiManipulatorCHK->setFocusPolicy(Qt::StrongFocus);
        uiManipulatorCHK->setAutoFillBackground(false);
        uiManipulatorCHK->setAutoExclusive(true);

        gridLayout_2->addWidget(uiManipulatorCHK, 0, 2, 1, 1);

        uiCharacterCHK = new QCheckBox(uiTweenTypeWidget);
        uiCharacterCHK->setObjectName(QString::fromUtf8("uiCharacterCHK"));
        uiCharacterCHK->setEnabled(true);
        sizePolicy3.setHeightForWidth(uiCharacterCHK->sizePolicy().hasHeightForWidth());
        uiCharacterCHK->setSizePolicy(sizePolicy3);
        uiCharacterCHK->setFont(font1);
        uiCharacterCHK->setFocusPolicy(Qt::StrongFocus);
        uiCharacterCHK->setAutoFillBackground(false);
        uiCharacterCHK->setAutoExclusive(true);

        gridLayout_2->addWidget(uiCharacterCHK, 0, 3, 1, 1);

        uiGraphCHK = new QCheckBox(uiTweenTypeWidget);
        uiGraphCHK->setObjectName(QString::fromUtf8("uiGraphCHK"));
        uiGraphCHK->setEnabled(true);
        sizePolicy3.setHeightForWidth(uiGraphCHK->sizePolicy().hasHeightForWidth());
        uiGraphCHK->setSizePolicy(sizePolicy3);
        uiGraphCHK->setFont(font1);
        uiGraphCHK->setFocusPolicy(Qt::StrongFocus);
        uiGraphCHK->setAutoFillBackground(false);
        uiGraphCHK->setAutoExclusive(true);

        gridLayout_2->addWidget(uiGraphCHK, 0, 4, 1, 1);


        gridLayout_3->addWidget(uiTweenTypeWidget, 0, 0, 1, 1);


        gridLayout->addWidget(uiBreakdownGRP, 0, 0, 1, 1);

        QWidget::setTabOrder(uiKeyedCHK, uiMarkedCHK);
        QWidget::setTabOrder(uiMarkedCHK, uiManipulatorCHK);
        QWidget::setTabOrder(uiManipulatorCHK, uiCharacterCHK);
        QWidget::setTabOrder(uiCharacterCHK, uiGraphCHK);
        QWidget::setTabOrder(uiGraphCHK, uiTweenSLDR);
        QWidget::setTabOrder(uiTweenSLDR, uiSeek0BTN_2);
        QWidget::setTabOrder(uiSeek0BTN_2, uiSeek25BTN_3);
        QWidget::setTabOrder(uiSeek25BTN_3, uiSeek25BTN);
        QWidget::setTabOrder(uiSeek25BTN, uiSeek25BTN_2);
        QWidget::setTabOrder(uiSeek25BTN_2, uiSeek50BTN);
        QWidget::setTabOrder(uiSeek50BTN, uiSeek75BTN_2);
        QWidget::setTabOrder(uiSeek75BTN_2, uiSeek75BTN);
        QWidget::setTabOrder(uiSeek75BTN, uiSeek75BTN_3);
        QWidget::setTabOrder(uiSeek75BTN_3, uiSeek75BTN_4);
        QWidget::setTabOrder(uiSeek75BTN_4, uiSeek75BTN_5);
        QWidget::setTabOrder(uiSeek75BTN_5, uiSeek100BTN);

        retranslateUi(BlurTween);

        QMetaObject::connectSlotsByName(BlurTween);
    } // setupUi

    void retranslateUi(QWidget *BlurTween)
    {
        BlurTween->setWindowTitle(QApplication::translate("BlurTween", "BlurBetween", 0, QApplication::UnicodeUTF8));
        uiSeek0BTN_2->setText(QApplication::translate("BlurTween", "0", 0, QApplication::UnicodeUTF8));
        uiSeek25BTN->setText(QApplication::translate("BlurTween", "20", 0, QApplication::UnicodeUTF8));
        uiSeek100BTN->setText(QApplication::translate("BlurTween", "100", 0, QApplication::UnicodeUTF8));
        uiSeek50BTN->setText(QApplication::translate("BlurTween", "40", 0, QApplication::UnicodeUTF8));
        uiSeek75BTN->setText(QApplication::translate("BlurTween", "60", 0, QApplication::UnicodeUTF8));
        uiSeek75BTN_2->setText(QApplication::translate("BlurTween", "50", 0, QApplication::UnicodeUTF8));
        uiSeek25BTN_2->setText(QApplication::translate("BlurTween", "30", 0, QApplication::UnicodeUTF8));
        uiSeek25BTN_3->setText(QApplication::translate("BlurTween", "10", 0, QApplication::UnicodeUTF8));
        uiSeek75BTN_3->setText(QApplication::translate("BlurTween", "70", 0, QApplication::UnicodeUTF8));
        uiSeek75BTN_4->setText(QApplication::translate("BlurTween", "80", 0, QApplication::UnicodeUTF8));
        uiSeek75BTN_5->setText(QApplication::translate("BlurTween", "90", 0, QApplication::UnicodeUTF8));
        uiKeyedCHK->setText(QApplication::translate("BlurTween", "Keyed", 0, QApplication::UnicodeUTF8));
        uiMarkedCHK->setText(QApplication::translate("BlurTween", "Marked", 0, QApplication::UnicodeUTF8));
        uiManipulatorCHK->setText(QApplication::translate("BlurTween", "Manipulator", 0, QApplication::UnicodeUTF8));
        uiCharacterCHK->setText(QApplication::translate("BlurTween", "Character", 0, QApplication::UnicodeUTF8));
        uiGraphCHK->setText(QApplication::translate("BlurTween", "Graph", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BlurTween: public Ui_BlurTween {};
} // namespace Ui

QT_END_NAMESPACE

#endif // BLURBETWEEN_UI_H
