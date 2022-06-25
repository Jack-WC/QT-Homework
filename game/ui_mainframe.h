/********************************************************************************
** Form generated from reading UI file 'mainframe.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFRAME_H
#define UI_MAINFRAME_H

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

class Ui_MainFrame
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainFrame)
    {
        if (MainFrame->objectName().isEmpty())
            MainFrame->setObjectName(QStringLiteral("MainFrame"));
        MainFrame->resize(800, 600);
        menubar = new QMenuBar(MainFrame);
        menubar->setObjectName(QStringLiteral("menubar"));
        MainFrame->setMenuBar(menubar);
        centralwidget = new QWidget(MainFrame);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        MainFrame->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainFrame);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainFrame->setStatusBar(statusbar);

        retranslateUi(MainFrame);

        QMetaObject::connectSlotsByName(MainFrame);
    } // setupUi

    void retranslateUi(QMainWindow *MainFrame)
    {
        MainFrame->setWindowTitle(QApplication::translate("MainFrame", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class MainFrame: public Ui_MainFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFRAME_H
