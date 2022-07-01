#include "playwindow.h"
#include "ui_playwindow.h"
#include "player.h"
#include "levelpick.h"
#include <QtWidgets>
#include <vector>
#include <fstream>
#include<synchapi.h>
#include <QPainter>
#include<QTime>
#include<QTimer>
#include<QList>

const int PlayWindow::WIDTH = 1600;//界面宽度
const int PlayWindow::HEIGHT = 900;//界面高度
const int G_W=50;
const int G_H=50;
const int back_speed=5;//背景后移速度
const int changeinterval=15000;//背景切换时间间隔
int block_speed=16;//平台向后移动初速度，可调整
int delta_speed=1;//平台加速度（每changeinterval）
int mode=1;//记录背景种类（0/1/2）
int total_monster=0;//总怪物数
std::vector<QLabel*> monsters;//存储怪物
std::vector<QLabel*> gifts;//存储积分

PlayWindow::PlayWindow(int sign, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayWindow)
{
    ui->setupUi(this);
    setFixedSize(WIDTH, HEIGHT);

    chara4 = sign;
    paret = parent;

    //背景图片移动
    back_timer = new QTimer(this);
    connect(back_timer,SIGNAL(timeout()),this,SLOT(onTimer_backmove()));
    back_timer->start(back_speed);
    back1=new QLabel(this);
    back2=new  QLabel(this);
    back1->setScaledContents(true);
    back1->setPixmap(QPixmap(":/new/prefix1/Image/back.png"));
    back1->setGeometry(0,0,1600, 900);
    back2->setScaledContents(true);
    back2->setPixmap(QPixmap(":/new/prefix1/Image/back.png"));
    back2->setGeometry(1600,0,1600, 900);

    //平台块移动与产生
    blockmove_timer = new QTimer(this);
    blockbirth_timer[0]=new QTimer(this);blockbirth_timer[1]=new QTimer(this);blockbirth_timer[2]=new QTimer(this);
    connect(blockmove_timer,SIGNAL(timeout()),this,SLOT(onTimer_blockmove()));
    connect(blockbirth_timer[0],SIGNAL(timeout()),this,SLOT(onTimer_blockbirth1()));
    connect(blockbirth_timer[1],SIGNAL(timeout()),this,SLOT(onTimer_blockbirth2()));
    connect(blockbirth_timer[2],SIGNAL(timeout()),this,SLOT(onTimer_blockbirth3()));
    blockmove_timer->start(block_speed);
    blockbirth_timer[0]->start(1500);
    //引入随机数种子
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    //初始平台生成
    for(int i=0;i<15;i++){
        for(int j=0;j<2;j++){
            QLabel* ground=new QLabel(this);
            ground->setScaledContents(true);
            ground->setPixmap(QPixmap(":/new/prefix1/Image/ground"+QString::number(mode)+".png"));
            ground->setGeometry(i*100, 600+j*100 ,100, 100);
            ground->show();
            blocks.push_back(ground);
        }
    }

    //切换模式计时器
    changemode_timer=new QTimer(this);
    connect(changemode_timer,SIGNAL(timeout()),this,SLOT(onTimer_changemode()));
    changemode_timer->start(changeinterval);

    //怪物生成
    monsterbirth_timer=new QTimer(this);
    connect(monsterbirth_timer,SIGNAL(timeout()),this,SLOT(onTimer_monsterbirth()));
    monsterbirth_timer->start(3000);

    //主角
    player = new Player(sign, Player::towardRight, blocks, this);
    player->setGeometry(0, 500, 60, 100);

    //血条展示
    hp_label=new QLabel(this);
    hp_label->setScaledContents(true);
    hp_label->setGeometry(10,10,50*((player->getHp()+1)/2),50);
    hp_label->setPixmap(QPixmap(":/new/prefix1/Image/hp" + QString::number(player->getHp()) + ".png"));

    //积分展示
    credit=0;
    credit_show=new QLabel(this);
    credit_show->setGeometry(1400,750,200,150);
    credit_show->setFont(QFont("宋体", 40));
    QPalette p0;
    p0.setColor(QPalette::WindowText, Qt::red);
    credit_show->setPalette(p0);
    credit_show->setWordWrap(true);
    credit_show->setText(QString::number(credit));
    credit_label=new QLabel(this);

    //战斗计时器初始化
    timer_attack = new QTimer(this);
    connect(timer_attack,SIGNAL(timeout()),this,SLOT(onTimer_attack()));
    timer_attack->start(100);

    out_check = new QTimer(this);
    connect(out_check,SIGNAL(timeout()),this,SLOT(onTimer_out()));
    out_check->start(50);
}

PlayWindow::~PlayWindow()
{
    monsters.clear();gifts.clear();
    blocks.clear();
    block_speed=16; mode=1; total_monster=0;
    delete ui;
}

void PlayWindow::delay(int ms)
{
    QEventLoop loop;
    QTimer::singleShot(ms, &loop, SLOT(quit()));
    loop.exec();
}

void PlayWindow::onTimer_out()
{
    if(player->flag){
        credit_show->hide();
        credit_label->setGeometry(1200,600,400,300);
        credit_label->setFont(QFont("宋体", 40));
        QPalette p0;
        p0.setColor(QPalette::WindowText, Qt::red);
        credit_label->setPalette(p0);
        credit_label->setWordWrap(true);
        credit_label->setText("游戏结束orz\n你的得分为"+QString::number(credit));
        delay(2000);
        levelpick *win4 = new levelpick(chara4);
        win4->show();
        delete paret;
    }
}

void PlayWindow::onTimer_backmove()
{
    static int pos = 0;
    pos = (pos+1)%this->width();
    back1->setGeometry(-pos,0,this->width(),this->height());
    back2->setGeometry(this->width()-pos,0,this->width(),this->height());
}

//地图上所有平台/怪物/礼物向后移动
void PlayWindow::onTimer_blockmove()
{
    QList<QLabel*>::iterator p=blocks.begin();
    for(; p!=blocks.end();++p)
    {
        (*p)->setGeometry((*p)->geometry().translated(-5,0));
        if((*p)->geometry().x()+(*p)->geometry().width()<0)
        {
            delete (*p);
            p=blocks.erase(p);p--;
        }
    }
    std::vector<QLabel*>::iterator m=monsters.begin();
    for(; m!=monsters.end();++m)
    {
        (*m)->setGeometry((*m)->geometry().translated(-5,0));
        if((*m)->geometry().x()+(*m)->geometry().width()<0)
        {
            delete (*m);
            m=monsters.erase(m);m--;
            total_monster--;
        }
    }

    std::vector<QLabel*>::iterator n=gifts.begin();
    for(; n!=gifts.end();++n)
    {
        (*n)->setGeometry((*n)->geometry().translated(-5,0));
        if((*n)->geometry().x()+(*n)->geometry().width()<0)
        {
            delete (*n);
            n=gifts.erase(n);n--;
        }
    }
}

//生成礼物绘制
void PlayWindow::giftbirth(QLabel* block)
{
    int rand=qrand()%9;
    if(rand<3){
        QLabel* newgift=new QLabel(this);
        newgift->setScaledContents(true);
        if(rand) newgift->setPixmap(QPixmap(":/new/prefix1/Image/gift"+QString::number(mode)+".png"));
        else newgift->setPixmap(QPixmap(":/new/prefix1/Image/gift"+QString::number(mode)+QString::number(mode)+".png"));
        newgift->setGeometry(block->geometry().x()+block->geometry().width()/2, block->geometry().y()-60 ,50, 50);
        newgift->show();
        gifts.push_back(newgift);
    }
}

//生成平台绘制
void PlayWindow::createblock(int y,int w,int h)
{
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            QLabel* ground=new QLabel(this);
            ground->setScaledContents(true);
            ground->setPixmap(QPixmap(":/new/prefix1/Image/ground"+QString::number(mode)+".png"));
            ground->setGeometry(this->width()+i*100, y+j*100 ,100, 100);
            ground->show();
            blocks.push_back(ground);
            giftbirth(ground);
        }
    }
}

//随机产生新的区块模式1
 void PlayWindow::onTimer_blockbirth1()
 {
     //寻找最右边的区块
     QList<QLabel*>::iterator p=blocks.begin(); QList<QLabel*>::iterator q=blocks.begin();
     for(; p!=blocks.end();++p)
         if((*p)->geometry().x()+(*p)->geometry().width() > (*q)->geometry().x()+(*q)->geometry().width())
            q=p;
     QRect last_block=(*q)->geometry();
     if(last_block.x()+last_block.width()>1600) return;
     //随机位置
     int rand=qrand()%40-20;
     int rand2=qrand()%20-10;
     while(last_block.y()+rand*10>800) rand-=5;  while(last_block.y()+rand*10<300) rand+=5;
     while(last_block.y()+rand2*20>800) rand2-=2; while(last_block.y()+rand2*20<300) rand2+=2;
     int length=qrand()%3+1;
     int length2=qrand()%4+1;
     createblock(last_block.y()+rand*10,length,1);
     createblock(last_block.y()+rand2*20,length2,1);
 }
//产生模式2
 void PlayWindow::onTimer_blockbirth2()
 {
     static int num2=0;
     int rand=qrand()%2+1;
     int rand2=qrand()%17%2+2;
     int now_num2 =  -abs(num2 - 3)+3;
     createblock(-now_num2*100+500,rand,1);
     if(num2>0){
      createblock(now_num2*100+500,rand2,1);
     }
     num2=(num2+1)%6;
 }
//产生模式3
 void PlayWindow::onTimer_blockbirth3()
 {
        static int num3=0;
        int now_num3 = num3 < 9 ? -abs(num3 - 3)+6 : num3 - 9;
        int rand=qrand()%2+2;
        createblock( -now_num3*100+800,rand,1);
        num3=(num3+1)%12;
 }

 //产生怪物
 void PlayWindow::onTimer_monsterbirth()
 {
    if(total_monster>5) return;
    int rand=qrand()%60+10;
    QLabel* monster=new QLabel(this);
    monster->setScaledContents(true);
    monster->setPixmap(QPixmap(":/new/prefix1/Image/enemy"+QString::number(mode)+".png"));
    monster->setGeometry(this->width(), rand*10 ,70, 70);
    monster->show();
    monsters.push_back(monster);
    total_monster++;
 }

//改变平台产生模式
 void PlayWindow::changeBlockBirth()
 {
     int last;
     static int birthspeed=1500;
     static bool flag1=false;static bool flag2=false;
     for(int i=0;i<3;i++){
         if(blockbirth_timer[i]->isActive()){
            blockbirth_timer[i]->stop();
            last=i;
         }
     }
     if(block_speed<12&&!flag1){
        birthspeed=1200;
        flag1=true;
    }
     if(block_speed<9&&!flag2){
         birthspeed=900;
         flag2=true;
     }
     int rand=qrand()%3;if(rand==last) rand=(rand+1)%3;
     blockbirth_timer[rand]->start(birthspeed);
     blockmove_timer->stop();
     block_speed-=delta_speed;
     if(block_speed<0) exit(0);
     blockmove_timer->start(block_speed);
 }

//改变背景样式
 void PlayWindow::onTimer_changemode()
 {
     static int a[3]={1,0,0};
     static int total_mode=1;
     if(total_mode==3){
         a[0]=0,a[1]=0,a[2]=0;total_mode=0;
     }
     mode=qrand()%3+1;
     while(a[mode-1]){
         mode=mode%3+1;
     }
     a[mode-1]=1;
     ++total_mode;
     createblock(600,3,1);
     back1->setPixmap(QPixmap(":/new/prefix1/Image/back"+QString::number(mode)+".png"));
     back2->setPixmap(QPixmap(":/new/prefix1/Image/back"+QString::number(mode)+".png"));
     changeBlockBirth();    
 }

//判断主角和物体的位置关系
int mycheck(const Player *player, const QLabel* item)
{
    if(player->geometry().intersects(item->geometry()))
        return 1;
    else
        return 0;
}

//与怪物/礼物相遇函数
void PlayWindow::onTimer_attack()
{
    std::vector<QLabel*>::iterator m=monsters.begin();
    for(; m!=monsters.end();++m)
    {
        int result = mycheck(player, *m);
        if(result){//被怪物减血
            if(player->changeHp(1)){
                credit_show->hide();
                credit_label->setGeometry(1200,600,400,300);
                credit_label->setFont(QFont("宋体", 40));
                QPalette p0;
                p0.setColor(QPalette::WindowText, Qt::red);
                credit_label->setPalette(p0);
                credit_label->setWordWrap(true);
                credit_label->setText("游戏结束orz\n你的得分为"+QString::number(credit));
                delay(2000);
                levelpick *win4 = new levelpick(chara4);
                win4->show();
                delete paret;
            }
            showHp();
            delete (*m);
            m=monsters.erase(m);m--;
            total_monster--;
        }
    }

    std::vector<QLabel*>::iterator n=gifts.begin();//遇到礼物就增加积分
    for(; n!=gifts.end();++n)
    {
        int result = mycheck(player, *n);
        if(result){
            ++credit;
            showCredit();
            delete (*n);
            n=gifts.erase(n);n--;
        }
    }
}

void PlayWindow::showHp()
{
    hp_label->setGeometry(10,10,50*((player->getHp()+1)/2),50);
    hp_label->setPixmap(QPixmap(":/new/prefix1/Image/hp" + QString::number(player->getHp()) + ".png"));
}
void PlayWindow::showCredit()
{
   credit_show->setText(QString::number(credit));
 }

Player* PlayWindow::getPlayer()
{
    return player;
}
