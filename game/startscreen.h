#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QMainWindow>
#include<QLabel>
//开始界面

namespace Ui {
class StartScreen;
}

class StartScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = 0);
    ~StartScreen();

private:
    Ui::StartScreen *ui;

public slots:
    void onbutton1();
};

#endif // STARTSCREEN_H
