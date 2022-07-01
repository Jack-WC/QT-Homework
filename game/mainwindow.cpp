/*5.30修改内容：
 * 1.新增player角色类，删除原有protagonist、2个timer，将jump，move等函数移动到类中
 * 2.新增地图文件，程序启动时从map1.dat文件中加载（请关闭shadow build否则会加载失败！！）
 * 3.优化了部分代码
 * 提示：QLabel直接用QPixmap加载图片即可
*/
/*6.17修改内容：
 * 1.增加左右移动的动作差分，为此，改变角色图片命名方式为" type(0/1)+towards(left/right)+step(0-5).png"，同时修改原player的getPixmap()函数
 * 2.尝试增加片头动画（可点击右下角跳过）与开始界面（仅示意，后续再讨论修改），但qt播放视频需要另外的解码器，故另附K-Lite安装包
 * 3.尝试给人物增加血条，撞到怪物减血，血为零或者掉出界面自动退出
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"
#include "levelpick.h"
#include <QtWidgets>
#include <vector>
#include <fstream>
#include <synchapi.h>

const int MainWindow::WIDTH = 1600;//界面宽度
const int MainWindow::HEIGHT = 900;//界面高度
const int MainWindow::BLOCK_W = 100;//区块宽与高
const int MainWindow::BLOCK_H = 100;
const int C_W = 60;//人物宽与高
const int C_H = 100;
const int M_W = 50;//怪物宽度
const int M_H = 50;//怪物高度
const int M_Hurt = 1;//怪物伤害
const QPoint movePos[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

QString words_text = "关卡名称：初临幻境\n你发现自己来到了一个奇妙的地方\n环视四周，你发现远处有一个传送门\n向着传送门进发吧\n要小心怪物哦";

MainWindow::MainWindow(int sign, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    setFixedSize(WIDTH, HEIGHT);

    chara1 = sign;
    paret = parent;

    //背景
    background = new QLabel(this);
    background->resize(WIDTH, HEIGHT);
    background->setScaledContents(true);
    background->setAutoFillBackground(true);
    background->setPixmap(QPixmap(":/new/prefix1/Image/back.png"));

    words = new QLabel(this);
    words->setFont(QFont("宋体", 14));
    words->setWordWrap(true);
    words->setGeometry(1200,650,400,200);
    words->setText(words_text);

    //加载地图文件
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

    //主角
    player = new Player(sign, Player::towardRight, blocks, this);
    player->setGeometry(0, 700, C_W, C_H);

    //怪物生成
    for(int i=0; i<4; i++){
        monster[i] = new QLabel(this);
        monster[i]->setScaledContents(true);
        monster[i]->setGeometry(monster_pos[i].x(), monster_pos[i].y(), M_W, M_H);
        monster[i]->setPixmap(QPixmap(":/new/prefix1/Image/monster" + QString::number(i + 1) + ".png"));
    }

    //血条展示
    hpbar = new HpBar(player->getHp(), player->getMaxHp(), this);
    hpbar->move(50, 50);

    //怪物移动计时器初始化
    timer_monster[0] = new QTimer(this);
    connect(timer_monster[0],SIGNAL(timeout()),this,SLOT(onTimer_monster1()));
    direction1 = 0;//怪物初始移动方向
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
    door_check = new QTimer(this);
    connect(door_check,SIGNAL(timeout()),this,SLOT(onTimer_door()));
    door_check->start(100);

    out_check = new QTimer(this);
    connect(out_check,SIGNAL(timeout()),this,SLOT(onTimer_out()));
    out_check->start(50);
}

void MainWindow::delay(int ms)
{
    QEventLoop loop;
    QTimer::singleShot(ms, &loop, SLOT(quit()));
    loop.exec();
}

void MainWindow::onTimer_out()
{
    if(player->flag){
        words->setFont(QFont("宋体", 40));
        words->setText("游戏失败");
        delay(1000);
        levelpick *win1 = new levelpick(chara1);
        win1->show();
        delete paret;
    }
}

void MainWindow::onTimer_door()
{
    if(player->geometry().y() + C_H == 350 && player->geometry().x() < 100 - C_W){
        words->setFont(QFont("宋体", 40));
        words->setText("成功过关");
        delay(1000);
        levelpick *win1 = new levelpick(chara1);
        win1->show();
        delete paret;
    }
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

//判断主角和怪物的位置关系,1代表怪物死亡，2代表主角受伤
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
            if(player->changeHp(M_Hurt)){
                words->setFont(QFont("宋体", 40));
                words->setText("游戏失败");
                delay(1000);
                levelpick *win1 = new levelpick(chara1);
                win1->show();
                delete paret;
            }
            hpbar->decrease(M_Hurt);
            record[i] = 0;
            timer_monster[i]->stop();
            delete monster[i];
            delete timer_monster[i];
            monster[i] = nullptr;
            timer_monster[i] = nullptr;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

Player *MainWindow::getPlayer()
{
    return player;
}
