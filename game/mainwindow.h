#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>

//此处定义全局常量
extern const int GRAVITY; //重力
extern const int INTERVAL; //跳跃动画间隔（单位ms）
extern const QPoint movePos[4]; //移动方向数组

//第一关界面
class Player;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    const static int X;//界面宽度
    const static int Y;//界面高度
    const static int BLOCK_W;//方块宽度
    const static int BLOCK_H;//方块高度

    explicit MainWindow(int sign, QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event); //键盘按下
    void keyReleaseEvent(QKeyEvent *event); //键盘释放
    std::vector<QLabel*> &getBlocks();

public slots:
    void onTimer_monster1();
    void onTimer_monster2();
    void onTimer_monster3();
    void onTimer_monster4();
    void onTimer_attack();
    void onTimer_player();

private:
    Ui::MainWindow *ui;
    Player *player;
    QPoint monster_pos[4] = {{400, 650}, {1200, 250}, {500, 150}, {100, 300}};
    QLabel *background;//背景
    QLabel *monster[4];//怪物
    QLabel *door;//传送门
    QTimer *player_timer; //人物横向移动计时器
    QTimer *timer_monster[4];//怪物移动计时器
    QTimer *timer_attack;//战斗计时器
    int turns;//记录跳跃过程
    int direction1, direction2, direction3, direction4;//记录怪物移动方向
    int record[4];//记录怪物死亡情况
    bool left_pressed, right_pressed, up_pressed;

    void playerMove(); //玩家移动函数
};

#endif // MAINWINDOW_H
