/*5.30修改内容：
 * 1.新增player角色类，删除原有protagonist、2个timer，将jump，move等函数移动到类中
 * 2.新增地图文件，程序启动时从map1.dat文件中加载（请关闭shadow build否则会加载失败！！）
 * 3.优化了部分代码
 * 提示：QLabel直接用QPixmap加载图片即可
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"
#include <QtWidgets>
#include <vector>
#include <fstream>

const int MainWindow::X = 1600;//界面宽度
const int MainWindow::Y = 900;//界面高度
const int MainWindow::BLOCK_W = 100;
const int MainWindow::BLOCK_H = 100;
const int C_W = 60;
const int C_H = 100;
const int M_W = 50;//怪物宽度
const int M_H = 50;//怪物高度
const int GRAVITY = 1000;
const int INTERVAL = 10;
const QPoint movePos[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

std::vector<QLabel*> blocks; //存储方块

MainWindow::MainWindow(int sign, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(X, Y);

    //背景
    background = new QLabel(this);
    background->resize(X,Y);
    background->setScaledContents(true);
    background->setAutoFillBackground(true);
    background->setPixmap(QPixmap(":/new/prefix1/Image/back.png"));

    //主角
    player = new Player(sign, Player::towardRight, this);
    player->setGeometry(0, 700, C_W, C_H);

    //加载地图文件
    qDebug() << QDir::currentPath() << endl;
    std::ifstream mapfile("./data/map1.dat");
    if(mapfile.is_open())
    {
        while(!mapfile.eof())
        {
            double x, y;
            mapfile >> x >> y;
            QLabel *label = new QLabel(this);
            label->setScaledContents(true);
            label->setPixmap(QPixmap(":/new/prefix1/Image/ground.png"));
            label->setGeometry(BLOCK_W * x, BLOCK_H * y, BLOCK_W, BLOCK_H);
            blocks.push_back(label);
        }
        mapfile.close();
    }
    else
        qDebug() << "Map data file cannot open" << endl;

    //怪物生成
    for(int i=0; i<4; i++){
        monster[i] = new QLabel(this);
        monster[i]->setScaledContents(true);
        monster[i]->setGeometry(monster_pos[i].x(), monster_pos[i].y(), M_W, M_H);
        monster[i]->setPixmap(QPixmap(":/new/prefix1/Image/monster" + QString::number(i + 1) + ".png"));
    }
    //人物移动计时器
    player_timer = new QTimer(this);
    connect(player_timer, SIGNAL(timeout()), this, SLOT(onTimer_player()));

    //怪物移动计时器初始化
    timer_monster[0] = new QTimer(this);
    connect(timer_monster[0],SIGNAL(timeout()),this,SLOT(onTimer_monster1()));
    direction1 = 0;
    timer_monster[0]->start(100);

    timer_monster[1] = new QTimer(this);
    connect(timer_monster[1],SIGNAL(timeout()),this,SLOT(onTimer_monster2()));
    direction2 = 0;
    timer_monster[1]->start(100);

    timer_monster[2] = new QTimer(this);
    connect(timer_monster[2],SIGNAL(timeout()),this,SLOT(onTimer_monster3()));
    direction3 = 0;
    timer_monster[2]->start(100);

    timer_monster[3] = new QTimer(this);
    connect(timer_monster[3],SIGNAL(timeout()),this,SLOT(onTimer_monster4()));
    direction4 = 0;
    timer_monster[3]->start(100);

    //战斗计时器初始化
    timer_attack = new QTimer(this);
    connect(timer_attack,SIGNAL(timeout()),this,SLOT(onTimer_attack()));
    timer_attack->start(100);
    for(int i=0; i<4; i++){
        record[i] = 1;
    }

    //传送门
    door = new QLabel(this);
    door->setScaledContents(true);
    door->setPixmap(QPixmap(":/new/prefix1/Image/door.png"));
    door->setGeometry(0,250,100,100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//怪物移动函数
void MainWindow::onTimer_monster1()
{
    QPoint position;
    position = monster[0]->pos();
    if(direction1 == 0){
        monster[0]->setGeometry(position.x()+10,position.y(),M_W,M_H);
        if(position.x()+10 == 850){
            direction1 = 1;
        }
    }
    else if(direction1 == 1){
        monster[0]->setGeometry(position.x()-10,position.y(),M_W,M_H);
        if(position.x()-10 == 400){
            direction1 = 0;
        }
    }
}

void MainWindow::onTimer_monster2()
{
    QPoint position;
    position = monster[1]->pos();
    if(direction2 == 0){
        monster[1]->setGeometry(position.x()+10,position.y(),M_W,M_H);
        if(position.x()+10 == 1550){
            direction2 = 1;
        }
    }
    else if(direction2 == 1){
        monster[1]->setGeometry(position.x()-10,position.y(),M_W,M_H);
        if(position.x()-10 == 1200){
            direction2 = 0;
        }
    }
}

void MainWindow::onTimer_monster3()
{
    QPoint position;
    position = monster[2]->pos();
    if(direction3 == 0){
        monster[2]->setGeometry(position.x()+10,position.y(),M_W,M_H);
        if(position.x()+10 == 650){
            direction3 = 1;
        }
    }
    else if(direction3 == 1){
        monster[2]->setGeometry(position.x()-10,position.y(),M_W,M_H);
        if(position.x()-10 == 500){
            direction3 = 0;
        }
    }
}

void MainWindow::onTimer_monster4()
{
    QPoint position;
    position = monster[3]->pos();
    if(direction4 == 0){
        monster[3]->setGeometry(position.x()+10,position.y(),M_W,M_H);
        if(position.x()+10 == 350){
            direction4 = 1;
        }
    }
    else if(direction4 == 1){
        monster[3]->setGeometry(position.x()-10,position.y(),M_W,M_H);
        if(position.x()-10 == 100){
            direction4 = 0;
        }
    }
}

//判断主角和怪物的位置关系,1代表怪物死亡，2代表主角死亡
int check_attack(const Player *player, const QLabel* monster)
{
    if(player->geometry().intersects(monster->geometry()))
        return player->getVerticalSpeed() > 0 ? 1 : 2;
    else
        return 0;
}

//战斗函数
void MainWindow::onTimer_attack()
{
    int result[4];
    for(int i=0; i<4; i++){
        if(monster[i] != nullptr)
            result[i] = check_attack(player, monster[i]);
    }
    for(int i=0; i<4; i++){
        if(result[i] == 1 && record[i] == 1){
            record[i] = 0;
            timer_monster[i]->stop();
            delete monster[i];
            delete timer_monster[i];
            monster[i] = nullptr;
            timer_monster[i] = nullptr;
        }
        else if(result[i] == 2 && record[i] == 1){
            exit(0);
        }
    }
}

void MainWindow::onTimer_player()
{
    if(player->getTowards() == Player::towardLeft)
        player->move(Player::moveLeft, 2);
    else
        player->move(Player::moveRight, 2);
}

void MainWindow::playerMove()
{
    if(up_pressed)
        player->jump(800);
    if(left_pressed)
    {
        if(player->getTowards() != Player::towardLeft)
            player->setTowards(Player::towardLeft);
        player_timer->start(INTERVAL);
    }
    if(right_pressed)
    {
        if(player->getTowards() != Player::towardRight)
            player->setTowards(Player::towardRight);
        player_timer->start(INTERVAL);
    }
}

//键盘响应
void MainWindow::keyPressEvent(QKeyEvent *event)
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
    playerMove();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
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
            player_timer->stop();
        }
        break;
    case Qt::Key_D:
        if(!event->isAutoRepeat() && right_pressed)
        {
            right_pressed = false;
            player_timer->stop();
        }
        break;
    default:
        break;
    }
}

std::vector<QLabel*> &MainWindow::getBlocks()
{
    return blocks;
}
