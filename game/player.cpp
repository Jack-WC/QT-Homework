#include "player.h"
#include <QtWidgets>

Player::Player(int type_, int init_towards, MainWindow *parent_)
    : QLabel(parent_), type(type_), parent(parent_), towards(init_towards)
{
    setScaledContents(true);
    setPixmap(getPixmap(type, towards));
    timer = new QTimer(parent);
    connect(timer, &QTimer::timeout, this, &Player::vertical_move);
}

QPixmap Player::getPixmap(int type, int towards)
{
    QString prefix(":/new/prefix1/Image/");
    switch(type)
    {
    case 1:
        return towards == 0 ? QPixmap(prefix + "left1.png") : QPixmap(prefix + "right1.png");
    case 2:
        return towards == 0 ? QPixmap(prefix + "left2.png") : QPixmap(prefix + "right2.png");
    default:
        qDebug() << "Invalid character" << endl;
        return QPixmap();
    }
}

bool Player::isOutOfBorder(int dir, int step)
{
    QRect dest_rect = geometry().translated(step * movePos[dir]); //获取平移后矩形
    QRect map_rect(0, -200, MainWindow::X, MainWindow::Y + 400); //地图矩形
    return dest_rect.intersected(map_rect) != dest_rect;
}

void Player::vertical_move() //上下移动
{ 
    //qDebug() << "vmove" << endl;
    int step = vertical_speed * ((double)INTERVAL / 1000);
    int dir = step > 0 ? 1 : 0; //移动方向
    vertical_speed += GRAVITY * ((double)INTERVAL / 1000); //加速
    if(!move(dir, abs(step))) //碰到障碍，速度变为0
    {
        vertical_speed = 0;
    }
}

void Player::jump(int init_speed) //人物跳跃
{
    if(timer->isActive())
    {
        //qDebug() << "return" << endl;
        return;
    }
    vertical_speed = -init_speed; //设置初速度
    timer->start(INTERVAL);
}

bool Player::isCollidedWithBlocks(int dir, int step, QRect &cross_rect)
{
    QRect dest_rect = geometry().translated(step * movePos[dir]); //获取平移后矩形
    std::vector<QLabel*> blocks = parent->getBlocks();
    for(auto block : blocks)
    {
        cross_rect = dest_rect.intersected(block->geometry());
        if(cross_rect.width() > 1 && cross_rect.height() > 1) //与障碍物碰撞
        {
            return true;
        }
    }
    return false;
}

void Player::moveEvent(QMoveEvent *event) //人物移动事件处理
{
    if(pos().y() >= MainWindow::Y) //掉出画面，游戏失败
        exit(0);
    if(isInSpace()) //踩空
    {
        jump(0);
    }
    else
    {
        if(timer->isActive())
        {
            timer->stop();
            vertical_speed = 0;
        }
    }
    event->accept();
}

bool Player::isInSpace()
{
    std::vector<QLabel*> blocks = parent->getBlocks();
    QPoint bottom_left = geometry().bottomLeft();
    QPoint bottom_right = geometry().bottomRight();
    for(auto block : blocks)
    {
        QPoint top_left = block->geometry().topLeft();
        QPoint top_right = block->geometry().topRight();
        if(top_left.y() - bottom_left.y() <= 1 && top_left.y() - bottom_left.y() >= 0
           && bottom_right.x() >= top_left.x() && top_right.x() >= bottom_left.x()) //判断是否与地面相交
        {
            return false;
        }
    }
    return true;
}

bool Player::move(int dir, int step)
{
    if(isOutOfBorder(dir, step))
        return false;
    QRect cross_rect;
    if(isCollidedWithBlocks(dir, step, cross_rect))
    {
        if(dir == 0 || dir == 1) //步长过大，尽可能移动
            move(dir, step - cross_rect.height());
        else
            move(dir, step - cross_rect.width());
        return false;
    }
    setGeometry(geometry().translated(step * movePos[dir]));
    return true;
}

int Player::getTowards()
{
    return towards;
}

void Player::setTowards(int towards)
{
    this->towards = towards;
    setPixmap(getPixmap(type, towards));
}

int Player::getVerticalSpeed() const
{
    return vertical_speed;
}

