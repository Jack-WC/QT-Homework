#ifndef FAIL_H
#define FAIL_H

#include <QMainWindow>

//游戏失败界面

namespace Ui {
class fail;
}

class fail : public QMainWindow
{
    Q_OBJECT

public:
    explicit fail(QWidget *parent = 0);
    ~fail();

private:
    Ui::fail *ui;
};

#endif // FAIL_H
