#ifndef OP_H
#define OP_H

#include <QWidget>
#include<QMediaPlayer>
#include<QVideoWidget>

namespace Ui {
class OP;
}
class QMediaPlayer;
class QVideoWidget;
class OP : public QWidget
{
    Q_OBJECT

public:
    explicit OP(QWidget *parent = 0);
    ~OP();

private:
    Ui::OP *ui;
    QMediaPlayer* mediaplayer;
    QVideoWidget* videoWidget;

public slots:
    void playerEnd(QMediaPlayer::MediaStatus status);
    void onbutton();
};

#endif // OP_H
