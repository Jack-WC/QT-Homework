#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "hpbar.h"
#include <vector>
#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>

//此处定义全局常量
extern const int C_W;//人物宽与高
extern const int C_H;
extern const int M_W;//怪物宽度
extern const int M_H;//怪物高度
extern const int WALKINTERVAL;//走路动画差分时间间隔，调到30以上会出bug，目前不清楚原因
extern const int M_Hurt;//怪物伤害
extern const int GRAVITY; //重力
extern const int INTERVAL; //跳跃动画间隔（单位ms）
extern const QPoint movePos[4]; //移动方向数组

//第一关界面
class Player;

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    const static int WIDTH, HEIGHT, BLOCK_W, BLOCK_H;

    explicit MainWindow(int sign, QWidget *parent = 0);
    ~MainWindow();
    Player *getPlayer();

public slots:
    void onTimer_monster1();
    void onTimer_monster2();
    void onTimer_monster3();
    void onTimer_monster4();
    void onTimer_attack();

private:
    Ui::MainWindow *ui;
    Player *player;
    QPoint monster_pos[4] = {{400, 650}, {1200, 250}, {500, 150}, {100, 300}};//怪物位置
    QLabel *background;//背景
    QLabel *monster[4];//怪物
    QLabel *door;//传送门
    HpBar *hpbar;
    QTimer *timer_monster[4];//怪物移动计时器
    QTimer *timer_attack;//战斗计时器
    QList<QLabel*> blocks;
    int turns;//记录跳跃过程
    int direction1, direction2, direction3, direction4;//记录怪物移动方向
    int record[4];//记录怪物死亡情况
};

#endif // MAINWINDOW_H
