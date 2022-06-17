/********************************************************************************
** Form generated from reading UI file 'op.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OP_H
#define UI_OP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OP
{
public:

    void setupUi(QWidget *OP)
    {
        if (OP->objectName().isEmpty())
            OP->setObjectName(QStringLiteral("OP"));
        OP->resize(1400, 900);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        OP->setFont(font);

        retranslateUi(OP);

        QMetaObject::connectSlotsByName(OP);
    } // setupUi

    void retranslateUi(QWidget *OP)
    {
        OP->setWindowTitle(QApplication::translate("OP", "\346\224\273\345\237\216\347\213\256\347\232\204\345\245\207\345\246\231\345\206\222\351\231\251", 0));
    } // retranslateUi

};

namespace Ui {
    class OP: public Ui_OP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OP_H
