/********************************************************************************
** Form generated from reading UI file 'startscreen.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTSCREEN_H
#define UI_STARTSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartScreen
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StartScreen)
    {
        if (StartScreen->objectName().isEmpty())
            StartScreen->setObjectName(QStringLiteral("StartScreen"));
        StartScreen->resize(1600, 900);
        centralwidget = new QWidget(StartScreen);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        StartScreen->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StartScreen);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1600, 26));
        StartScreen->setMenuBar(menubar);
        statusbar = new QStatusBar(StartScreen);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        StartScreen->setStatusBar(statusbar);

        retranslateUi(StartScreen);

        QMetaObject::connectSlotsByName(StartScreen);
    } // setupUi

    void retranslateUi(QMainWindow *StartScreen)
    {
        StartScreen->setWindowTitle(QApplication::translate("StartScreen", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class StartScreen: public Ui_StartScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTSCREEN_H
