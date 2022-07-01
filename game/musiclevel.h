#ifndef MUSICLEVEL_H
#define MUSICLEVEL_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QLabel>
#include <QTimer>
#include <QQueue>
#include <QKeyEvent>

//第三关界面

namespace Ui {
class musiclevel;
}

class musiclevel : public QMainWindow
{
    Q_OBJECT

public:
    const static int X;//界面宽度
    const static int Y;//界面高度
    const static int STROKE_W;//按键宽度
    const static int STROKE_H;//按键高度
    const static int gap;

    explicit musiclevel(int sign, QWidget *parent = 0);
    ~musiclevel();
    void display();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::musiclevel *ui;
    int type;
    QMediaPlayer *mediaplayer;//音乐
    QLabel *player;//主角
    QLabel *background;//背景
    QTimer *playtime;//播放时间
    QLabel *spot;//标记
    QLabel *score;//分数
    QLabel *tips;//指示
    QQueue<int> spotmemory;//记录时间
    QQueue<int> positionmemory;//记录位置
    QTimer *temptimer;
    QTimer *jump;
    QTimer *down;
    QTimer *action_timer;
    int score_;
    int time;//当前时间
    int position;//当前位置
    int turns;
    int flag;
    int jumpturns;
    int towards = 1;
    bool left_pressed = false;
    bool right_pressed = false;

    QPixmap getPixmap(int type, int towards); //获取图片
    void check_player();
    void keyAction(bool left, bool right);
    void endMove();
    void move(int towd);
    void setTowards(int towards_);
    void delay(int ms);

public slots:
    void playerEnd(QMediaPlayer::MediaStatus status);
    void onTimer_playtime();
    void onTimer_temptimer();
    void onTimer_jump();
    void onTimer_down();
    void onTimer_action();
};

#endif // MUSICLEVEL_H
