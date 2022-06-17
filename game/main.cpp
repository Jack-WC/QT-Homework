#include "mainwindow.h"
#include "pick.h"
#include "op.h"
#include <QApplication>
#include <QLabel>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OP op_widget;
    op_widget.show();   
    /*//直接到选人界面
    pick pick_widget;
    pick_widget.show();
    */
    return a.exec();
}
