#include "hpbar.h"
#include <QDebug>

HpBar::HpBar(int hp, int max_hp, QWidget *parent) : QWidget(parent)
{
    this->hp = hp;
    this->max_hp = max_hp;
    resize(max_hp * WIDTH, WIDTH);
    for(int i = 0; i < (max_hp + 1) / 2; i++)
    {
        QLabel *heart = new QLabel(this);
        heart->setGeometry(i * WIDTH, 0, WIDTH, WIDTH);
        heart->setScaledContents(true);
        hp_label.push_back(heart);
    }
    setHp(hp);
}

void HpBar::setHp(int hp)
{
    if(hp > max_hp)
        return;
    this->hp = hp;
    int heartNum = (hp + 1) / 2;
    for(int i = 0; i < heartNum; i++)
    {
        if(i == heartNum - 1)
        {
            if(hp % 2)
                hp_label[i]->setPixmap(QPixmap(":/new/prefix1/Image/hp1.png"));
            else
                hp_label[i]->setPixmap(QPixmap(":/new/prefix1/Image/hp2.png"));
        }
        else
            hp_label[i]->setPixmap(QPixmap(":/new/prefix1/Image/hp2.png"));
    }
    for(int i = heartNum; i < (max_hp + 1) / 2; i++)
    {
        hp_label[i]->setPixmap(QPixmap(""));
    }
}

void HpBar::decrease(int delta)
{
    setHp(hp - delta);
}

int HpBar::getHp()
{
    return hp;
}
