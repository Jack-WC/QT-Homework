#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include<QList>

//第四关界面

class Player;

namespace Ui {
class PlayWindow;
}

class PlayWindow : public QWidget
{
    Q_OBJECT

public:
    const static int WIDTH, HEIGHT;
    explicit PlayWindow(int sign,QWidget *parent = 0);
    Player *getPlayer();
    void showHp();
    void showCredit();
    void changeBlockBirth();
    void createblock(int,int,int);
    ~PlayWindow();

public slots:
    void onTimer_attack();
    void onTimer_blockmove();
    void onTimer_blockbirth1();
    void onTimer_blockbirth2();
    void onTimer_blockbirth3();
    void onTimer_monsterbirth();
    void onTimer_changemode();
    void onTimer_backmove();
    void onTimer_out();

private:
    Ui::PlayWindow *ui;
    QWidget *paret;
    QTimer *back_timer;
    QTimer* blockmove_timer;
    QTimer* blockbirth_timer[3];
    QTimer* monsterbirth_timer;
    QTimer* changemode_timer;
    QTimer *timer_attack;//战斗计时器
    QTimer *out_check;
    QLabel* hp_label;
    QLabel* credit_label;
    QLabel* credit_show;
    QLabel* back1;
    QLabel* back2;
    Player *player;
    QList<QLabel*> blocks;
    int chara4;
    int credit;
    void giftbirth(QLabel*);
    void delay(int ms);
};

#endif // PLAYWINDOW_H
