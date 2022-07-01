/********************************************************************************
** Form generated from reading UI file 'levelpick.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEVELPICK_H
#define UI_LEVELPICK_H

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

class Ui_levelpick
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *levelpick)
    {
        if (levelpick->objectName().isEmpty())
            levelpick->setObjectName(QStringLiteral("levelpick"));
        levelpick->resize(800, 600);
        menubar = new QMenuBar(levelpick);
        menubar->setObjectName(QStringLiteral("menubar"));
        levelpick->setMenuBar(menubar);
        centralwidget = new QWidget(levelpick);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        levelpick->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(levelpick);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        levelpick->setStatusBar(statusbar);

        retranslateUi(levelpick);

        QMetaObject::connectSlotsByName(levelpick);
    } // setupUi

    void retranslateUi(QMainWindow *levelpick)
    {
        levelpick->setWindowTitle(QApplication::translate("levelpick", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class levelpick: public Ui_levelpick {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEVELPICK_H
