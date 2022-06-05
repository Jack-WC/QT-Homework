/********************************************************************************
** Form generated from reading UI file 'pick.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICK_H
#define UI_PICK_H

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

class Ui_pick
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *pick)
    {
        if (pick->objectName().isEmpty())
            pick->setObjectName(QStringLiteral("pick"));
        pick->resize(800, 600);
        menubar = new QMenuBar(pick);
        menubar->setObjectName(QStringLiteral("menubar"));
        pick->setMenuBar(menubar);
        centralwidget = new QWidget(pick);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pick->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(pick);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        pick->setStatusBar(statusbar);

        retranslateUi(pick);

        QMetaObject::connectSlotsByName(pick);
    } // setupUi

    void retranslateUi(QMainWindow *pick)
    {
        pick->setWindowTitle(QApplication::translate("pick", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class pick: public Ui_pick {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICK_H
