#include "player.h"
#include <QtWidgets>

const int Player::INTERVAL = 10; //走路移动时间间隔
const int Player::WALKINTERVAL = 50;//走路动画差分时间间隔，调到30以上会出bug，目前不清楚原因

Player::Player(int type_, int init_towards, QList<QLabel*> &ground_arr_, QWidget *parent)
    : QLabel(parent), type(type_), ground_arr(ground_arr_), towards(init_towards)
{
    setScaledContents(true);
    setPixmap(getPixmap(type, towards));

    //初始化计时器
    jump_timer = new QTimer(this);
    walk_timer = new QTimer(this);
    action_timer = new QTimer(this);
    connect(jump_timer, &QTimer::timeout, this, &Player::vertical_move);
    connect(walk_timer, &QTimer::timeout, this, &Player::onTimer_walk);
    connect(action_timer, &QTimer::timeout, this, &Player::onTimer_player);
}

QPixmap Player::getPixmap(int type, int towards)
{
    QString prefix(":/new/prefix1/Image/");
    QString nowtowards= towards== 0 ? "left" : "right";
    return QPixmap(prefix +QString::number(type)+ nowtowards+"2.png");
}

bool Player::isOutOfBorder(int dir, int step)
{
    QRect dest_rect = geometry().translated(step * movePos[dir]); //获取平移后矩形
    QRect map_rect(0, -200, MainWindow::WIDTH, MainWindow::HEIGHT + 400); //地图矩形
    return dest_rect.intersected(map_rect) != dest_rect;
}

void Player::vertical_move() //上下移动
{
    int step = vertical_speed * ((double)INTERVAL / 1000);
    int dir = step > 0 ? 1 : 0; //移动方向
    vertical_speed += gravity * ((double)INTERVAL / 1000); //加速
    if(!move(dir, abs(step))) //碰到障碍，速度变为0
        vertical_speed = 0;
}

void Player::jump(int init_speed) //人物跳跃
{
    if(jump_timer->isActive())
        return;
    vertical_speed = -init_speed; //设置初速度,以向下为速度正方向
    jump_timer->start(INTERVAL);
}

bool Player::isCollidedWithBlocks(int dir, int step, QRect &cross_rect)
{
    QRect dest_rect = geometry().translated(step * movePos[dir]); //获取平移后矩形
    for(auto block : ground_arr)
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
    if(pos().y() >= MainWindow::HEIGHT) //掉出画面，游戏失败
    {
        flag = 1;
    }
    if(isInSpace()) //踩空
        jump(0);
    else//在地面上
    {
        if(vertical_speed > 0 && jump_timer->isActive())
        {
            jump_timer->stop();
            vertical_speed = 0;
        }
    }
    event->accept();
}

bool Player::isInSpace()
{
    QPoint bottom_left = geometry().bottomLeft();
    QPoint bottom_right = geometry().bottomRight();
    for(int i = 0; i < ground_arr.size(); i++)
    {
        auto block = ground_arr[i];
        QPoint top_left = block->geometry().topLeft();
        QPoint top_right = block->geometry().topRight();
        if(top_left.y() - bottom_left.y() <= 1 && top_left.y() - bottom_left.y() >= 0
           && bottom_right.x() >= top_left.x() && top_right.x() >= bottom_left.x()) //判断是否与地面相交
        {
            if(vertical_speed > 0)
                emit land(i);
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

void Player::keyAction(bool up, bool left, bool right)
{
    if(up)
        jump(800);
    if(left || right)
    {
        if(left && towards != towardLeft)
            setTowards(towardLeft);
        else if(right && towards != towardRight)
            setTowards(towardRight);
        if(!action_timer->isActive())
            action_timer->start(INTERVAL);
        if(!walk_timer->isActive())
            walk_timer->start(WALKINTERVAL);
    }
}

void Player::endMove(){
    action_timer->stop();
    walk_timer->stop();
    walk_step = 0;
    setTowards(towards);
}

void Player::setSpeed(int speed)
{
    this->speed = speed;
}

void Player::setGravity(int gravity)
{
    this->gravity = gravity;
}

void Player::onTimer_player()
{
    move(towards == towardLeft ? moveLeft : moveRight, speed);
}

//走路动画
void Player::onTimer_walk()
{
    //if(vertical_speed==0){//在空中左右移动是否需要走路动画？这里默认需要，如果不想要就删掉前面的注释号
    int now_step = walk_step < 6 ? -abs(walk_step - 1)+5 : walk_step - 6;
    QString prefix(":/new/prefix1/Image/");
    QString nowtowards = towards == towardLeft ? "left" : "right";
    setPixmap(QPixmap(prefix +QString::number(type)+ nowtowards + QString::number(now_step)+".png"));
    walk_step=(walk_step+1)%10;
    //}
}

int Player::getTowards()
{
    return towards;
}

int Player::getType()
{
    return type;
}

void Player::setMaxHp(int max_hp)
{
    this->max_hp = max_hp;
}

int Player::getMaxHp()
{
    return max_hp;
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

int Player::getHp()
{
    return hp;
}

bool Player::changeHp(int delta)
{
    hp-=delta;
    if(hp<=0)
        return true;
    else
        return false;
}

