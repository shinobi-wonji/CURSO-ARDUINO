/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_1;
    QSlider *sliderGripper;
    QLabel *label_4;
    QLabel *label_2;
    QSlider *sliderShoulder;
    QDial *dialBase;
    QSlider *sliderElbow;
    QCheckBox *checkBox;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(651, 300);
        QIcon icon;
        icon.addFile(QStringLiteral("ArmDesktop.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 1, 3, 1, 1);

        label_1 = new QLabel(centralWidget);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_1, 1, 0, 1, 1);

        sliderGripper = new QSlider(centralWidget);
        sliderGripper->setObjectName(QStringLiteral("sliderGripper"));
        sliderGripper->setMaximum(180);
        sliderGripper->setValue(90);
        sliderGripper->setTracking(false);
        sliderGripper->setOrientation(Qt::Vertical);

        gridLayout->addWidget(sliderGripper, 0, 4, 1, 1, Qt::AlignHCenter);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 1, 4, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        sliderShoulder = new QSlider(centralWidget);
        sliderShoulder->setObjectName(QStringLiteral("sliderShoulder"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sliderShoulder->sizePolicy().hasHeightForWidth());
        sliderShoulder->setSizePolicy(sizePolicy);
        sliderShoulder->setMaximum(180);
        sliderShoulder->setValue(90);
        sliderShoulder->setTracking(false);
        sliderShoulder->setOrientation(Qt::Vertical);

        gridLayout->addWidget(sliderShoulder, 0, 1, 1, 1, Qt::AlignHCenter);

        dialBase = new QDial(centralWidget);
        dialBase->setObjectName(QStringLiteral("dialBase"));
        dialBase->setMaximum(360);
        dialBase->setValue(180);
        dialBase->setTracking(false);

        gridLayout->addWidget(dialBase, 0, 0, 1, 1);

        sliderElbow = new QSlider(centralWidget);
        sliderElbow->setObjectName(QStringLiteral("sliderElbow"));
        sliderElbow->setMaximum(180);
        sliderElbow->setValue(90);
        sliderElbow->setTracking(false);
        sliderElbow->setOrientation(Qt::Vertical);

        gridLayout->addWidget(sliderElbow, 0, 3, 1, 1, Qt::AlignHCenter);


        gridLayout_2->addLayout(gridLayout, 0, 1, 2, 1);

        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout_2->addWidget(checkBox, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ArmDesktop", 0));
        label_3->setText(QApplication::translate("MainWindow", "Elbow", 0));
        label_1->setText(QApplication::translate("MainWindow", "Base", 0));
        label_4->setText(QApplication::translate("MainWindow", "Gripper", 0));
        label_2->setText(QApplication::translate("MainWindow", "Shoulder", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Led13", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
