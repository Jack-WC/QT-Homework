#include "fail.h"
#include "ui_fail.h"

fail::fail(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fail)
{
    ui->setupUi(this);
}

fail::~fail()
{
    delete ui;
}
