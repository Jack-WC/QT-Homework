#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "player.h"
#include "hpbar.h"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    const static int WIDTH, HEIGHT, BLOCK_W, BLOCK_H, C_H, C_W, INTERVAL, BLOCK_NUM, TOTAL_ROUND;

    Player *getPlayer();
    explicit Game(int character_type, QWidget *parent = nullptr);
    ~Game();

private:
    Ui::Game *ui;
    Player *player;
    HpBar *hpbar;
    QList<QLabel*> ground_arr;
    QTimer *word_timer;
    QTimer *flicker_timer; //灯光闪烁计时器
    QLabel *description;
    QLabel *status; //显示当前状态（回合以及要跳的方块数）
    QLabel *hint; //提示用户信息
    int index = 0; //文字说明滚动下标
    int round = 0; //当前回合
    int seqLen = 0; //序列长度
    int flickerBlockIndex = -1; //当前闪烁方块在randomSeq中的下标
    int playerBlock = -1; //当前玩家该跳方块的下标
    QList<int> randomSeq;
    bool allowJump = false;

    void startGame(int round);
    void delay(int ms);


private slots:
    void changeDescription();
    void blockFlicker();
    void playerLand(int id);
};

#endif // GAME_H
