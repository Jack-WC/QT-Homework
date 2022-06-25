#include "mainwindow.h"
#include "pick.h"
#include "op.h"
#include "mainframe.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    OP op_widget;
//    op_widget.show();
    /*//直接到选人界面
    pick pick_widget;
    pick_widget.show();
    */
    //MainWindow window(1);
    //window.show();
    //Game game(1);
    //game.show();
    MainFrame window;
    window.show();
    return a.exec();
}
