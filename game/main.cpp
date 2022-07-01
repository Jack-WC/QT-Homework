#include "mainwindow.h"
#include "pick.h"
#include "op.h"
#include "mainframe.h"
#include "musiclevel.h"
#include "levelpick.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OP op_widget;
    op_widget.show();

    return a.exec();
}
