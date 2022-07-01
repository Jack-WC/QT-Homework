#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "game.h"
#include "mainwindow.h"
#include <QMainWindow>

namespace Ui {
class MainFrame;
}

class MainFrame : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainFrame(int level, int character, QWidget *parent = 0);
    ~MainFrame();

private:
    QWidget *cwidget; //中心界面
    Player *player;
    bool left_pressed = false;
    bool right_pressed = false;
    bool up_pressed = false;
    Ui::MainFrame *ui;

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
};

#endif // MAINFRAME_H
