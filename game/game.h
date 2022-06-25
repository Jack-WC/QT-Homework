#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "player.h"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    const static int WIDTH, HEIGHT, GROUND_Y, BLOCK_W, BLOCK_H, C_H, C_W, INTERVAL;

    Player *getPlayer();
    explicit Game(int character_type, QWidget *parent = nullptr);
    ~Game();

private:
    Ui::Game *ui;
    Player *player;
    QList<QLabel*> ground_arr;
    QTimer *word_timer;
    QLabel *description;
    int index = 0;

private slots:
    void changeDescription();
};

#endif // GAME_H
