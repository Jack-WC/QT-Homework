/********************************************************************************
** Form generated from reading UI file 'fail.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAIL_H
#define UI_FAIL_H

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

class Ui_fail
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *fail)
    {
        if (fail->objectName().isEmpty())
            fail->setObjectName(QStringLiteral("fail"));
        fail->resize(800, 600);
        menubar = new QMenuBar(fail);
        menubar->setObjectName(QStringLiteral("menubar"));
        fail->setMenuBar(menubar);
        centralwidget = new QWidget(fail);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        fail->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(fail);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        fail->setStatusBar(statusbar);

        retranslateUi(fail);

        QMetaObject::connectSlotsByName(fail);
    } // setupUi

    void retranslateUi(QMainWindow *fail)
    {
        fail->setWindowTitle(QApplication::translate("fail", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class fail: public Ui_fail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAIL_H
