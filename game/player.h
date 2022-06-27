#ifndef PLAYER_H
#define PLAYER_H

#include <QtWidgets>
#include "mainwindow.h"

class Player;

class Player : public QLabel
{
    Q_OBJECT

public:
    Player(int type_, int init_towards, QList<QLabel*> &ground_arr_, QWidget *parent);
    bool isInSpace();
    void jump(int init_speed);
    bool move(int dir, int step); //dir:0123分别为上下左右,step为步长
    void setTowards(int towards);
    int getTowards();
    int getVerticalSpeed() const;
    int getType();
    int walk_step=0;
    void setMaxHp(int max_hp);
    int getMaxHp();
    int getHp();
    bool changeHp(int delta);
    void keyAction(bool up, bool left, bool right);
    void endMove();
    void setSpeed(int speed);
    void setGravity(int gravity);

    enum //方向与朝向的枚举类型
    {
        moveUp = 0,
        moveDown = 1,
        moveLeft = 2,
        moveRight = 3,
        towardLeft = 0,
        towardRight = 1,
    };
    static const int INTERVAL, WALKINTERVAL;

public slots:
    void vertical_move();
    void onTimer_player();
    void onTimer_walk();

private:
    MainWindow *parent;
    QTimer *walk_timer; //行走计时器
    QTimer *jump_timer; //跳跃计时器
    QTimer *action_timer; //动画计时器
    int type; //角色类型
    int towards = 1; //朝向:0为左，1为右
    int vertical_speed = 0; //垂直速度，以向下为正方向
    int max_hp = 12;
    int hp = max_hp;//血量，不超过12
    int speed = 2; //行走速度
    int gravity = 1000; //重力
    QList<QLabel*> &ground_arr; //障碍物与地面数组

    QPixmap getPixmap(int type, int towards); //获取图片
    bool isOutOfBorder(int dir, int step); //判断是否出界
    bool isCollidedWithBlocks(int dir, int step, QRect &cross_rect); //判断是否碰撞，若碰撞，则cross_rect为碰撞矩形大小
    void moveEvent(QMoveEvent *event);

signals:
    void land(int id); //发出落地信号
};

#endif // PLAYER_H
