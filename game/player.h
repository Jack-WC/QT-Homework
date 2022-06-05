#ifndef PLAYER_H
#define PLAYER_H

#include <QtWidgets>
#include "mainwindow.h"

class Player;

class Player : public QLabel
{
    //Q_OBJECT

public:
    Player(int type_, int init_towards, MainWindow *parent_);
    bool isInSpace();
    void jump(int init_speed);
    bool move(int dir, int step); //dir:0123分别为上下左右，step为步长
    void setTowards(int towards);
    int getTowards();
    int getVerticalSpeed() const;
    enum //方向与朝向的枚举类型
    {
        moveUp = 0,
        moveDown = 1,
        moveLeft = 2,
        moveRight = 3,
        towardLeft = 0,
        towardRight = 1,
    };

public slots:
    void vertical_move();

private:
    MainWindow *parent;
    QTimer *timer; //跳跃计时器
    int type; //角色类型
    int towards = 1; //朝向:0为左，1为右
    int vertical_speed = 0; //垂直速度，以向下为正方向

    QPixmap getPixmap(int type, int towards); //获取图片
    bool isOutOfBorder(int dir, int step); //判断是否出界
    bool isCollidedWithBlocks(int dir, int step, QRect &cross_rect); //判断是否碰撞，若碰撞，则cross_rect为碰撞矩形大小
    void moveEvent(QMoveEvent *event);
};

#endif // PLAYER_H
