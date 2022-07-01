#include "musiclevel.h"
#include "ui_musiclevel.h"
#include "levelpick.h"
#include <QMediaPlayer>
#include <QLabel>
#include <QTimer>
#include <QQueue>
#include <fstream>

const int musiclevel::X = 1600;//界面宽度
const int musiclevel::Y = 900;//界面高度
const int musiclevel::STROKE_W = 100;//按键宽度
const int musiclevel::STROKE_H = 300;//按键高度
const int musiclevel::gap = 50;
const int C_W = 60;//人物宽与高
const int C_H = 100;
const int line = 500;
const int dir = 10;
const int plus = 100;
const int towardLeft = 0;
const int towardRight = 1;
const int INTERVAL = 10;
const int speed = 2;

musiclevel::musiclevel(int sign, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::musiclevel)
{
    ui->setupUi(this);
    setFixedSize(X, Y);

    //背景
    background = new QLabel(this);
    background->resize(X,Y);
    background->setScaledContents(true);
    background->setAutoFillBackground(true);
    background->setPixmap(QPixmap(":/new/prefix1/Image/space.png"));
    for(int i=0; i<16; i++){
        QLabel *label = new QLabel(this);
        label->setScaledContents(true);
        label->setPixmap(QPixmap(":/new/prefix1/Image/keystroke.png"));
        label->setGeometry(STROKE_W * i, Y - STROKE_H, STROKE_W, STROKE_H);
    }

    spot = new QLabel(this);
    spot->setScaledContents(true);
    spot->setPixmap(QPixmap(":/new/prefix1/Image/spot.png"));
    spot->setVisible(false);

    score = new QLabel(this);
    score->setGeometry(700,20,900,100);
    score->setFont(QFont("Microsoft YaHei", 50));
    QPalette p1;
    p1.setColor(QPalette::WindowText, Qt::blue);
    score->setPalette(p1);
    score->setText("0");
    score_ = 0;

    tips = new QLabel(this);
    tips->setGeometry(1250,250,350,200);
    tips->setFont(QFont("宋体", 14));
    tips->setWordWrap(true);
    QPalette p2;
    p2.setColor(QPalette::WindowText, Qt::yellow);
    tips->setPalette(p2);
    tips->setText("关卡名称：星空演奏会\n这次你来到了一片星海之中\n音乐已经响起！\n开始演奏吧！\n(按下W开始游戏,A和D控制角色)\n(尽量使角色落入黑键中)");

    flag = 0;
    type = sign;

    //主角
    player = new QLabel(this);
    player->setScaledContents(true);
    player->setPixmap(getPixmap(sign, towards));
    player->setGeometry(0, line, C_W, C_H);

    action_timer = new QTimer(this);
    connect(action_timer, &QTimer::timeout, this, &musiclevel::onTimer_action);

    //读取数据
    temptimer = new QTimer(this);
    connect(temptimer,SIGNAL(timeout()),this,SLOT(onTimer_temptimer()));
    std::ifstream musicfile("./data/music.dat");
    if(musicfile.is_open())
    {
        while(!musicfile.eof())
        {
            int x, y;
            musicfile >> x >> y;
            spotmemory.enqueue(x);
            positionmemory.enqueue(y);
        }
        musicfile.close();
    }
    else
        qDebug() << "Music data file cannot open" << endl;

    //音乐
    mediaplayer = new QMediaPlayer(this);
    connect(mediaplayer,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(playerEnd(QMediaPlayer::MediaStatus)));
    mediaplayer->setMedia(QUrl::fromLocalFile("../game/Image/Rubia.mp3"));

    playtime = new QTimer(this);
    connect(playtime,SIGNAL(timeout()),this,SLOT(onTimer_playtime()));    

    jump = new QTimer(this);
    connect(jump,SIGNAL(timeout()),this,SLOT(onTimer_jump()));
    jumpturns = 0;
    down = new QTimer(this);
    connect(down,SIGNAL(timeout()),this,SLOT(onTimer_down()));
}

musiclevel::~musiclevel()
{
    delete ui;
}

void musiclevel::delay(int ms)
{
    QEventLoop loop;
    QTimer::singleShot(ms, &loop, SLOT(quit()));
    loop.exec();
}

void musiclevel::playerEnd(QMediaPlayer::MediaStatus status)
{
    if(status==QMediaPlayer::EndOfMedia){
        jump->stop();
        down->stop();
        tips->setGeometry(600,250,400,200);
        tips->setFont(QFont("宋体", 30));
        tips->setText("   游戏结束\n看看你的得分吧");
        tips->setVisible(true);
        delay(4000);
        levelpick *win3 = new levelpick(type);
        win3->show();
        delete this;
    }
}

void musiclevel::onTimer_down()
{
    QPoint pot = player->pos();
    player->setGeometry(pot.x(), pot.y() + dir, C_W, C_H);
    if(pot.y() + dir == line){
        jump->start(50);
        down->stop();
    }
}

void musiclevel::onTimer_jump()
{
    if(jumpturns == 20){
        jump->stop();
        down->start(50);
        jumpturns = 0;
    }
    QPoint pot = player->pos();
    player->setGeometry(pot.x(), pot.y() - dir, C_W, C_H);
    jumpturns++;
}

void musiclevel::check_player()
{
    int player_x = player->pos().x();
    if(player_x > STROKE_W * position - C_W && player_x < STROKE_W * (position + 1)){
        score_ += plus;
        score->setText(QString::number(score_));
    }
}

void musiclevel::onTimer_temptimer()
{
    if(turns == 1){
        spot->setVisible(true);
    }
    if(turns == 6){
        check_player();
    }
    if(turns == 7){
        temptimer->stop();
        spot->setVisible(false);
    }
    spot->setGeometry(STROKE_W * position, Y - gap * turns, STROKE_W, gap * turns);
    turns++;
}

void musiclevel::display()
{
    position = positionmemory.dequeue();
    turns = 1;
    temptimer->start(200);
}

void musiclevel::onTimer_playtime()
{
    time = mediaplayer->position();
    time /= 100;

    if(!spotmemory.isEmpty()){
        if(time == spotmemory.head()){
            spotmemory.dequeue();
            display();
        }
    }
}

QPixmap musiclevel::getPixmap(int type, int towards)
{
    QString prefix(":/new/prefix1/Image/");
    QString nowtowards= towards== 0 ? "left" : "right";
    return QPixmap(prefix +QString::number(type)+ nowtowards+"2.png");
}

void musiclevel::move(int towd)
{
    int xx = player->x();
    int yy = player->y();
    if(towd == 0){
        if(xx - speed >= 0){
            player->setGeometry(xx - speed, yy, C_W, C_H);
        }
    }
    else{
        if(xx + speed <= 1600 - C_W){
            player->setGeometry(xx + speed, yy, C_W, C_H);
        }
    }
}

void musiclevel::onTimer_action()
{
    move(towards);
}

void musiclevel::setTowards(int towards_)
{
    towards = towards_;
    player->setPixmap(getPixmap(type, towards));
}

void musiclevel::keyAction(bool left, bool right)
{
    if(left || right)
    {
        if(left && towards != towardLeft)
            setTowards(towardLeft);
        else if(right && towards != towardRight)
            setTowards(towardRight);
        if(!action_timer->isActive())
            action_timer->start(INTERVAL);
    }
}

//键盘响应
void musiclevel::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_W:
        if(flag == 0){
            tips->setVisible(false);
            mediaplayer->play();
            playtime->start(50);
            jump->start(50);
            flag = 1;
        }
        break;
    case Qt::Key_A:
        if(!event->isAutoRepeat() && !left_pressed)
            left_pressed = true;
        break;
    case Qt::Key_D:
        if(!event->isAutoRepeat() && !right_pressed)
            right_pressed = true;
        break;
    case Qt::Key_R:
        levelpick *win3 = new levelpick(type);
        win3->show();
        delete this;
        break;
    }
    keyAction(left_pressed, right_pressed);
}

void musiclevel::endMove(){
    action_timer->stop();
    setTowards(towards);
}

void musiclevel::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_A:
        if(!event->isAutoRepeat() && left_pressed)
        {
            left_pressed = false;
            endMove();
        }
        break;
    case Qt::Key_D:
        if(!event->isAutoRepeat() && right_pressed)
        {
            right_pressed = false;
            endMove();
        }
        break;
    default:
        break;
    }
}
