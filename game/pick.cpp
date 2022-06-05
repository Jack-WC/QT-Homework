#include "pick.h"
#include "ui_pick.h"
#include "mainwindow.h"
#include <QPushButton>

const int X=1600;//界面宽度
const int Y=900;//界面高度
const int C_W=30*5;//角色宽度
const int C_H=50*5;//角色高度

pick::pick(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pick)
{
    ui->setupUi(this);
    resize(X,Y);

    //背景
    QLabel *background = new QLabel(this);
    background->resize(X,Y);
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
    QMainWindow *level = new MainWindow(1);
    level->show();
    delete this;
}

void pick::onbutton2()
{
    QMainWindow *level = new MainWindow(2);
    level->show();
    delete this;
}
