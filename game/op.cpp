#include "op.h"
#include "ui_op.h"
#include "pick.h"
#include"startscreen.h"
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QLabel>

const int X=1400;//界面宽度
const int Y=900;//界面高度

OP::OP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OP)
{
    ui->setupUi(this);
    //背景
    QLabel *background = new QLabel(this);
    background->resize(X,Y);
    background->setScaledContents(true);
    background->setAutoFillBackground(true);
    background->setPixmap(QPixmap(":/new/prefix1/Image/background.png"));

    //快进按钮
    QPushButton *button = new QPushButton(this);
    button->setGeometry(1300,800,60,50);
    button->setIcon(QIcon(":/new/prefix1/Image/skip.png"));
    button->setIconSize(QSize(80,50));
    connect(button,SIGNAL(clicked()),this,SLOT(onbutton()));

    //播放视频
    mediaplayer= new QMediaPlayer(this);
    videoWidget=new QVideoWidget(this);
    videoWidget->resize(1200,898);
    videoWidget->move(100,0);
    mediaplayer->setVideoOutput(videoWidget);
    mediaplayer->setMedia(QUrl::fromLocalFile("../game/Image/op.mp4"));
    connect(mediaplayer,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(playerEnd(QMediaPlayer::MediaStatus)));
    mediaplayer->play();
}

OP::~OP()
{
    delete ui;
}

void OP::playerEnd(QMediaPlayer::MediaStatus status)
{
    if(status==QMediaPlayer::EndOfMedia){
        StartScreen* start_widget=new StartScreen();
        start_widget->show();
        delete this;
    }
}

void OP::onbutton()
{
    StartScreen* start_widget=new StartScreen();
    start_widget->show();
    delete this;
}
