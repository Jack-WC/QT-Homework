#include "startscreen.h"
#include "ui_startscreen.h"
#include "pick.h"
#include <QPushButton>

StartScreen::StartScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);

    //背景
    QLabel *background = new QLabel(this);
    background->resize(MainWindow::WIDTH,MainWindow::HEIGHT);
    background->setScaledContents(true);
    background->setAutoFillBackground(true);
    background->setPixmap(QPixmap(":/new/prefix1/Image/back.png"));

    //标题
    QLabel *words = new QLabel(this);
    words->setGeometry(200,100,1200,150);
    words->setFont(QFont("Microsoft YaHei", 50));
    words->setText("攻城狮的奇妙冒险（未定，测试");

    //图片展示
    QLabel *character1 = new QLabel(this);
    character1->setScaledContents(true);
    character1->setPixmap(QPixmap(":/new/prefix1/Image/character1.png"));
    character1->setGeometry(650,250,C_W,C_H);

    //选择按钮
    QPushButton *button1 = new QPushButton("开始游戏",this);
    button1->setGeometry(720,750,160,100);
    connect(button1,SIGNAL(clicked()),this,SLOT(onbutton1()));

}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::onbutton1()
{
    pick* pick_widget=new pick();
    pick_widget->show();
    delete this;
}
