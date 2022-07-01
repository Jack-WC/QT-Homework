#include "levelpick.h"
#include "mainframe.h"
#include "musiclevel.h"
#include "ui_levelpick.h"
#include <QLabel>
#include <QPushButton>

levelpick::levelpick(int chara_, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::levelpick)
{
    ui->setupUi(this);
    setFixedSize(1600, 900);
    chara = chara_;

    //背景
    QLabel *background = new QLabel(this);
    background->resize(1600, 900);
    background->setScaledContents(true);
    background->setAutoFillBackground(true);
    background->setPixmap(QPixmap(":/new/prefix1/Image/back.png"));

    //文字
    QLabel *words = new QLabel(this);
    words->setGeometry(600,0,500,200);
    words->setFont(QFont("Microsoft YaHei", 50));
    words->setText("关卡选择");
    QLabel *Rw = new QLabel(this);
    Rw->setGeometry(610,200,400,100);
    Rw->setFont(QFont("Microsoft YaHei", 20));
    Rw->setText("按R键可退出当前关卡");

    //选择按钮
    QPushButton *button1 = new QPushButton("第1关",this);
    QPushButton *button2 = new QPushButton("第2关",this);
    QPushButton *button3 = new QPushButton("第3关",this);
    QPushButton *button4 = new QPushButton("第4关",this);
    button1->setGeometry(280,400,100,100);
    button2->setGeometry(580,400,100,100);
    button3->setGeometry(880,400,100,100);
    button4->setGeometry(1180,400,100,100);
    connect(button1,SIGNAL(clicked()),this,SLOT(onbutton1()));
    connect(button2,SIGNAL(clicked()),this,SLOT(onbutton2()));
    connect(button3,SIGNAL(clicked()),this,SLOT(onbutton3()));
    connect(button4,SIGNAL(clicked()),this,SLOT(onbutton4()));
}

levelpick::~levelpick()
{
    delete ui;
}

void levelpick::onbutton1()
{
    MainFrame *win = new MainFrame(1, chara);
    win->show();
    delete this;
}

void levelpick::onbutton2()
{
    MainFrame *win = new MainFrame(2, chara);
    win->show();
    delete this;
}

void levelpick::onbutton3()
{
    musiclevel *win = new musiclevel(chara);
    win->show();
    delete this;
}

void levelpick::onbutton4()
{
    MainFrame *win = new MainFrame(4, chara);
    win->show();
    delete this;
}
