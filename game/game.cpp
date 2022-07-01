#include "game.h"
#include "ui_game.h"
#include "mainwindow.h"
#include "player.h"
#include "synchapi.h"
#include "levelpick.h"
#include <algorithm>
#include <ctime>

const int Game::WIDTH = MainWindow::WIDTH;
const int Game::HEIGHT = MainWindow::HEIGHT;
const int Game::BLOCK_W = MainWindow::BLOCK_W;
const int Game::BLOCK_H = MainWindow::BLOCK_H;
const int Game::C_H = 100;
const int Game::C_W = 60;
const int Game::INTERVAL = 2000; //文字滚动时间间隔
const int Game::BLOCK_NUM = 10;
const int Game::TOTAL_ROUND = 5;

/*
 * 关卡名称：记忆迷阵
 * 玩法：本关卡一共有5轮。在每一轮当中，地面上的方块将会按一定的顺序随机闪烁，不会有多个方块同时闪烁。
 * 方块闪烁完毕后，你需要根据方块闪烁的顺序完成跳跃，出现错误则会受到惩罚，损失一点生命值，并重新开始本轮跳跃。
 * 每一轮考验的难度逐渐递增，完成所有考验即可过关
 * 存在问题：跳跃的判定按最左边的方块进行，有可能出现错误，所以尽量避免在方块边界处落地
*/

QString describe_text[5] = {"你来到了一个神秘的地方", "这个地方看起来虽然平淡无奇，但是地面却暗藏玄机", "你注意到，地面有时会有方块发出亮光，这或许是神的指引？", "追随这一亮光，你或许就能找到前进的方向",
                           "关卡名称：记忆迷阵\n关卡说明：这一关有5轮考验，在每一轮考验当中，你需要按照神的指引，在亮光结束后，按顺序跳跃到之前发出亮光的方格上，如果跳到错误的方格上，你会面临神的惩罚（损失一点生命值）。每一轮考验都会比之前更加困难，祝你好运！"};

Game::Game(int character_type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    setFixedSize(WIDTH, HEIGHT);
    chara2 = character_type;
    paret = parent;

    //初始化背景
    QLabel *background = new QLabel(this);
    background->resize(WIDTH, HEIGHT);
    background->setScaledContents(true);
    background->setAutoFillBackground(true);
    background->setPixmap(QPixmap(":/new/prefix1/Image/back.png"));

    description = new QLabel(this);
    description->setText(describe_text[index]);
    description->setFont(QFont("宋体", 14));
    description->setAlignment(Qt::AlignHCenter);
    description->setWordWrap(true);
    description->setGeometry((WIDTH - 600) / 2, 100, 600, 300);

    status = new QLabel(this);
    status->setGeometry(50, 100, 400, 200);
    status->setFont(QFont("宋体", 14));
    status->setAlignment(Qt::AlignHCenter);
    hint = new QLabel(this);
    hint->setGeometry(WIDTH - 450, 100, 400, 200);
    hint->setFont(QFont("宋体", 14));
    hint->setAlignment(Qt::AlignHCenter);

    //初始化地面
    int bw = WIDTH / BLOCK_NUM;
    for(int i = 0; i < BLOCK_NUM; i++)
    {
        QLabel *ground = new QLabel(this);
        ground->setPixmap(QPixmap(":/new/prefix1/Image/ground.png"));
        ground->setScaledContents(true);
        ground->setGeometry(i * bw, HEIGHT - bw, bw, bw);
        ground_arr.push_back(ground);
    }

    //初始化玩家
    player = new Player(character_type, Player::towardRight, ground_arr, this);
    player->setGeometry(0, HEIGHT - bw - C_H, C_W, C_H);
    player->setSpeed(3);
    player->setGravity(1500);

    hpbar = new HpBar(player->getHp(), player->getMaxHp(), this);
    hpbar->move(50, 50);

    word_timer = new QTimer(this);
    connect(word_timer, &QTimer::timeout, this, &Game::changeDescription);
    word_timer->start(INTERVAL);
    flicker_timer = new QTimer(this);
    connect(flicker_timer, &QTimer::timeout, this, &Game::blockFlicker);
    connect(player, &Player::land, this, &Game::playerLand);

    out_check = new QTimer(this);
    connect(out_check,SIGNAL(timeout()),this,SLOT(onTimer_out()));
    out_check->start(50);
}

Game::~Game()
{
    delete ui;
}

void Game::onTimer_out()
{
    if(player->flag){
        levelpick *win2 = new levelpick(chara2);
        win2->show();
        delete paret;
    }
}

void Game::blockFlicker()
{
    int id = randomSeq[flickerBlockIndex];
    ground_arr[id]->setPixmap(QPixmap(":/new/prefix1/Image/ground_flicker.png"));
    delay(500);
    ground_arr[id]->setPixmap(QPixmap(":/new/prefix1/Image/ground.png"));
    flickerBlockIndex++;
    if(flickerBlockIndex == seqLen)
    {
        flicker_timer->stop();
        allowJump = true;
        hint->setText("请开始跳跃");
    }
}

void Game::delay(int ms)
{
    QEventLoop loop;//定义一个新的事件循环
    QTimer::singleShot(ms, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
    loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
}

void Game::playerLand(int id)
{
    if(!allowJump)
        return;
    if(id == randomSeq[playerBlock]) //踩到正确方块
    {
        allowJump = false;
        ground_arr[id]->setPixmap(QPixmap(":/new/prefix1/Image/ground_correct.png"));
        delay(500);
        ground_arr[id]->setPixmap(QPixmap(":/new/prefix1/Image/ground.png"));
        playerBlock++;
        status->setText(QString::asprintf("当前回合：%d 总回合：%d\n已跳方块数：%d 总方块数：%d", round, TOTAL_ROUND, playerBlock, seqLen));
        allowJump = true;
        if(playerBlock == seqLen)
        {
            round++;
            if(round == TOTAL_ROUND + 1)
            {
                hint->setText("你赢了！");
                delay(1000);
                levelpick *win2 = new levelpick(chara2);
                win2->show();
                delete paret;
            }
            else
            {
                hint->setText("恭喜您进入下一轮！");
                delay(1000);
                startGame(round);
            }
        }
    }
    else
    {
        allowJump = false;
        ground_arr[id]->setPixmap(QPixmap(":/new/prefix1/Image/ground_wrong.png"));
        hint->setText("跳跃方块错误！你受到了惩罚！");
        delay(500);
        ground_arr[id]->setPixmap(QPixmap(":/new/prefix1/Image/ground.png"));
        player->changeHp(1);
        if(player->getHp() == 0)
        {
            hint->setText("游戏失败orz");
            delay(1000);
            levelpick *win2 = new levelpick(chara2);
            win2->show();
            delete paret;
        }
        hpbar->decrease(1);
        delay(1000);
        startGame(round);
    }
}

void Game::startGame(int r)
{
    srand(time(0));
    allowJump = false;
    round = r;
    seqLen = r * 2 + 1;
    playerBlock = 0;
    randomSeq.clear();
    for(int i = 0; i < seqLen; i++)
        randomSeq.push_back(rand() % BLOCK_NUM);
    flickerBlockIndex = 0;
    flicker_timer->start(2000);
    status->setText(QString::asprintf("当前回合：%d 总回合：%d\n已跳方块数：%d 总方块数：%d", round, TOTAL_ROUND, playerBlock, seqLen));
    hint->setText("请等待方块闪烁完毕");
}

Player *Game::getPlayer()
{
    return player;
}

void Game::changeDescription()
{
    if(++index >= 4)
    {
        word_timer->stop();
        startGame(1);
    }
    description->setText(describe_text[index]);
}

