#include "help.h"
#include "ui_help.h"

help::help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
    this->setWindowTitle("模式介绍");
}

help::~help()
{
    delete ui;
}
