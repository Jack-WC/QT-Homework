/********************************************************************************
** Form generated from reading UI file 'playwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYWINDOW_H
#define UI_PLAYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayWindow
{
public:

    void setupUi(QWidget *PlayWindow)
    {
        if (PlayWindow->objectName().isEmpty())
            PlayWindow->setObjectName(QStringLiteral("PlayWindow"));
        PlayWindow->resize(400, 300);

        retranslateUi(PlayWindow);

        QMetaObject::connectSlotsByName(PlayWindow);
    } // setupUi

    void retranslateUi(QWidget *PlayWindow)
    {
        PlayWindow->setWindowTitle(QApplication::translate("PlayWindow", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class PlayWindow: public Ui_PlayWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYWINDOW_H
