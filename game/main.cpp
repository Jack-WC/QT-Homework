#include "mainwindow.h"
#include "pick.h"
#include <QApplication>
#include <QLabel>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pick pick_widget;
    pick_widget.show();
    return a.exec();
}
