#ifndef LEVELPICK_H
#define LEVELPICK_H

#include <QMainWindow>
#include <QPushButton>

//关卡选择界面

namespace Ui {
class levelpick;
}

class levelpick : public QMainWindow
{
    Q_OBJECT

public:
    explicit levelpick(int chara_, QWidget *parent = 0);
    ~levelpick();

public slots:
    void onbutton1();
    void onbutton2();
    void onbutton3();
    void onbutton4();

private:
    Ui::levelpick *ui;
    int chara;
};

#endif // LEVELPICK_H
