#ifndef PICK_H
#define PICK_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

//人物选择界面

namespace Ui {
class pick;
}

class pick : public QMainWindow
{
    Q_OBJECT

public:
    explicit pick(QWidget *parent = 0);
    ~pick();

public slots:
    void onbutton1();
    void onbutton2();

private:
    Ui::pick *ui;
};

#endif // PICK_H
