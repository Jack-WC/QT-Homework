#include "mainframe.h"
#include "ui_mainframe.h"
#include "game.h"
#include "mainwindow.h"
#include "playwindow.h"

MainFrame::MainFrame(int level, int character, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainFrame)
{
    setFixedSize(1600,900);

    if(level == 1){
        if(character == 1){
            cwidget = new MainWindow(1, this);
        }
        else{
            cwidget = new MainWindow(2, this);
        }
        player = ((MainWindow*)cwidget)->getPlayer();
    }
    else if(level == 2){
        if(character == 1){
            cwidget = new Game(1, this);
        }
        else{
            cwidget = new Game(2, this);
        }
        player = ((Game*)cwidget)->getPlayer();
    }
    else if(level == 4){
        if(character == 1){
            cwidget = new PlayWindow(1, this);
        }
        else{
            cwidget = new PlayWindow(2, this);
        }
        player = ((PlayWindow*)cwidget)->getPlayer();
    }
    setCentralWidget(cwidget);
    statusBar()->setVisible(false);
}

//键盘响应
void MainFrame::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_W:
        if(!event->isAutoRepeat() && !up_pressed) //解决qt长按重复调用press和release的问题
            up_pressed = true;
        break;
    case Qt::Key_A:
        if(!event->isAutoRepeat() && !left_pressed)
            left_pressed = true;
        break;
    case Qt::Key_D:
        if(!event->isAutoRepeat() && !right_pressed)
            right_pressed = true;
        break;
    default:
        break;
    }
    player->keyAction(up_pressed, left_pressed, right_pressed);
}

void MainFrame::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_W:
        if(!event->isAutoRepeat() && up_pressed)
            up_pressed = false;
        break;
    case Qt::Key_A:
        if(!event->isAutoRepeat() && left_pressed)
        {
            left_pressed = false;
            player->endMove();
        }
        break;
    case Qt::Key_D:
        if(!event->isAutoRepeat() && right_pressed)
        {
            right_pressed = false;
            player->endMove();
        }
        break;
    case Qt::Key_R:
        player->flag = 1;
        break;
    }
}

MainFrame::~MainFrame()
{
    delete ui;
}
