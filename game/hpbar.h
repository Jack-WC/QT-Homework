#ifndef HPBAR_H
#define HPBAR_H

#include <QList>
#include <QLabel>

class HpBar : public QWidget
{
    Q_OBJECT

private:
    int hp, max_hp;
    QList<QLabel*> hp_label;

public:
    static const int WIDTH = 30; //红心的大小

    HpBar(int hp, int max_hp, QWidget *parent = nullptr);
    void setHp(int hp);
    void decrease(int delta);
    int getHp();
};

#endif // HPBAR_H
