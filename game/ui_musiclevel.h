/********************************************************************************
** Form generated from reading UI file 'musiclevel.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSICLEVEL_H
#define UI_MUSICLEVEL_H

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

class Ui_musiclevel
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *musiclevel)
    {
        if (musiclevel->objectName().isEmpty())
            musiclevel->setObjectName(QStringLiteral("musiclevel"));
        musiclevel->resize(800, 600);
        menubar = new QMenuBar(musiclevel);
        menubar->setObjectName(QStringLiteral("menubar"));
        musiclevel->setMenuBar(menubar);
        centralwidget = new QWidget(musiclevel);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        musiclevel->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(musiclevel);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        musiclevel->setStatusBar(statusbar);

        retranslateUi(musiclevel);

        QMetaObject::connectSlotsByName(musiclevel);
    } // setupUi

    void retranslateUi(QMainWindow *musiclevel)
    {
        musiclevel->setWindowTitle(QApplication::translate("musiclevel", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class musiclevel: public Ui_musiclevel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICLEVEL_H
