#ifndef PICK_H
#define PICK_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "player.h"
#include "game.h"

//人物选择界面

namespace Ui {
class pick;
}

class pick : public QMainWindow
{
    Q_OBJECT

public:
    const static int WIDTH, HEIGHT, C_H, C_W;

    explicit pick(QWidget *parent = 0);
    ~pick();

public slots:
    void onbutton1();
    void onbutton2();

private:
    Ui::pick *ui;
};

#endif // PICK_H
