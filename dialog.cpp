#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("获胜");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setText(QString str)
{
    ui->label->setText(str);
}

void Dialog::on_buttonBox_accepted()
{
    exit(0);
}
