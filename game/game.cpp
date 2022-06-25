#include "game.h"
#include "ui_game.h"
#include "mainwindow.h"
#include "player.h"

const int Game::WIDTH = MainWindow::WIDTH;
const int Game::HEIGHT = MainWindow::HEIGHT;
const int Game::BLOCK_W = MainWindow::BLOCK_W;
const int Game::BLOCK_H = MainWindow::BLOCK_H;
const int Game::C_H = 100;
const int Game::C_W = 60;
const int Game::GROUND_Y = 800;
const int Game::INTERVAL = 2000; //文字滚动时间间隔

QString describe_text[5] = {"有一天，你来到了一个神秘的地方", "这个地方看起来虽然平淡无奇，但是地面却暗藏玄机", "你注意到，地面有时会有方块发出亮光，这或许是神的指引？", "追随这一亮光，你或许就能找到前进的方向",
                           "关卡说明：这一关有5轮考验，在每一轮考验当中，你需要按照神的指引，在亮光结束后，按顺序跳跃到之前发出亮光的方格上，如果跳到错误的方格上，你会面临神的惩罚（损失一点生命值）。每一轮考验都会比之前更加困难，祝你好运！"};

Game::Game(int character_type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    setFixedSize(WIDTH, HEIGHT);
    setWindowTitle("A Little Memory Game");

    //初始化背景
    QLabel *background = new QLabel(this);
    background->resize(WIDTH, HEIGHT);
    background->setScaledContents(true);
    background->setAutoFillBackground(true);
    background->setPixmap(QPixmap(":/new/prefix1/Image/back.png"));

    description = new QLabel(this);
    description->setText(describe_text[index]);
    description->setFont(QFont("黑体", 16));
    description->setAlignment(Qt::AlignHCenter);
    description->setWordWrap(true);
    description->setGeometry((WIDTH - 600) / 2, 100, 600, 300);

    word_timer = new QTimer(this);
    connect(word_timer, &QTimer::timeout, this, &Game::changeDescription);
    word_timer->start(INTERVAL);

    //初始化地面
    int ground_num = WIDTH / BLOCK_H;
    for(int i = 0; i < ground_num; i++)
    {
        QLabel *ground = new QLabel(this);
        ground->setPixmap(QPixmap(":/new/prefix1/Image/ground.png"));
        ground->setScaledContents(true);
        ground->setGeometry(i * BLOCK_W, GROUND_Y, BLOCK_W, BLOCK_H);
        ground_arr.push_back(ground);
    }

    //初始化玩家
    player = new Player(character_type, Player::towardRight, ground_arr, this);
    player->setGeometry(0, GROUND_Y - C_H, C_W, C_H);
}

Game::~Game()
{
    delete ui;
}

Player *Game::getPlayer()
{
    return player;
}

void Game::changeDescription()
{
    if(++index >= 4)
        word_timer->stop();
    description->setText(describe_text[index]);
}
