#include "pick.h"
#include "ui_pick.h"
#include "mainwindow.h"
#include "mainframe.h"
#include "levelpick.h"
#include <QPushButton>

const int pick::WIDTH=1600;//界面宽度
const int pick::HEIGHT=900;//界面高度
const int pick::C_W=30*5;//角色宽度
const int pick::C_H=50*5;//角色高度

pick::pick(QWidget *parent) : //pick继承自QMainWindow类
    QMainWindow(parent),
    ui(new Ui::pick)
{
    ui->setupUi(this);
    setFixedSize(WIDTH, HEIGHT);

    //背景
    QLabel *background = new QLabel(this);
    background->resize(WIDTH, HEIGHT);
    background->setScaledContents(true);
    background->setAutoFillBackground(true);
    background->setPixmap(QPixmap(":/new/prefix1/Image/back.png"));

    //文字
    QLabel *words = new QLabel(this);
    words->setGeometry(700,100,200,100);
    words->setFont(QFont("Microsoft YaHei", 20));
    words->setText("请选择角色:");

    //角色选择
    QLabel *character1 = new QLabel(this);
    character1->setScaledContents(true);
    character1->setPixmap(QPixmap(":/new/prefix1/Image/character1.png"));
    character1->setGeometry(350,250,C_W,C_H);

    QLabel *character2 = new QLabel(this);
    character2->setScaledContents(true);
    character2->setPixmap(QPixmap(":/new/prefix1/Image/character2.png"));
    character2->setGeometry(1100,250,C_W,C_H);

    //选择按钮
    QPushButton *button1 = new QPushButton("确认",this);
    QPushButton *button2 = new QPushButton("确认",this);
    button1->setGeometry(380,550,80,50);
    button2->setGeometry(1135,550,80,50);
    connect(button1,SIGNAL(clicked()),this,SLOT(onbutton1()));
    connect(button2,SIGNAL(clicked()),this,SLOT(onbutton2()));
}

pick::~pick()
{
    delete ui;
}

void pick::onbutton1()
{
    levelpick *lp = new levelpick(1);
    lp->show();
    delete this;
}

void pick::onbutton2()
{
    levelpick *lp = new levelpick(2);
    lp->show();
    delete this;
}
