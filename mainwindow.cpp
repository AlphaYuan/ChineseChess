#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chessboard.h"
#include "ai_search.h"
#include "dialog.h"
#include "onlinegame.h"
#include <QMessageBox>
#include "help.h"
#include <QInputDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("中国象棋");
    this->setWindowIcon(QIcon("logo.ico"));

    setObjectName("MainWindow");
    setStyleSheet("#MainWindow{border-image:url(:/img/images/welcome.jpg);}");

    ui->pushButton->setStyleSheet(
                "QPushButton{"
                "background-color:rgb(0, 0, 0);"
                "border-style:inset;"
                "border-width:2px;"
                "border-radius:10px;"
                "border-color:rgba(255,255,255,30);"
                "font:bold;"
                "color:white;"
                "padding:2px;"
                "}"
                "QPushButton:pressed{"
                "background-color:rgba(100,255,100,200);"
                "border-color:rgba(255,255,255,30);"
                "border-style:inset;"
                "color:rgba(0,0,0,100);"
                "}"
                "QPushButton:hover{"
                "background-color:rgba(100,255,100,100);"
                "border-color:rgba(255,255,255,200);"
                "color:rgba(0,0,0,200);"
                "}");
    ui->pushButton_2->setStyleSheet(

                "QPushButton{"
                "background-color:rgb(0, 0, 0);"
                "border-style:inset;"
                "border-width:2px;"
                "border-radius:10px;"
                "border-color:rgba(255,255,255,30);"
                "font:bold;"
                "color:white;"
                "padding:2px;"
                "}"

                "QPushButton:pressed{"
                "background-color:rgba(100,255,100,200);"
                "border-color:rgba(255,255,255,30);"
                "border-style:inset;"
                "color:rgba(0,0,0,100);"
                "}"

                "QPushButton:hover{"
                "background-color:rgba(100,255,100,100);"
                "border-color:rgba(255,255,255,200);"
                "color:rgba(0,0,0,200);"
                "}");
    ui->pushButton_3->setStyleSheet(

                "QPushButton{"
                "background-color:rgb(0, 0, 0);"
                "border-style:inset;"
                "border-width:2px;"
                "border-radius:10px;"
                "border-color:rgba(255,255,255,30);"
                "font:bold;"
                "color:white;"
                "padding:2px;"
                "}"

                "QPushButton:pressed{"
                "background-color:rgba(100,255,100,200);"
                "border-color:rgba(255,255,255,30);"
                "border-style:inset;"
                "color:rgba(0,0,0,100);"
                "}"

                "QPushButton:hover{"
                "background-color:rgba(100,255,100,100);"
                "border-color:rgba(255,255,255,200);"
                "color:rgba(0,0,0,200);"
                "}");

    ui->pushButton_4->setStyleSheet(

                "QPushButton{"
                "background-color:rgb(0, 0, 0);"
                "border-style:inset;"
                "border-width:2px;"
                "border-radius:10px;"
                "border-color:rgba(255,255,255,30);"
                "font:bold;"
                "color:white;"
                "padding:2px;"
                "}"

                "QPushButton:pressed{"
                "background-color:rgba(100,255,100,200);"
                "border-color:rgba(255,255,255,30);"
                "border-style:inset;"
                "color:rgba(0,0,0,100);"
                "}"

                "QPushButton:hover{"
                "background-color:rgba(100,255,100,100);"
                "border-color:rgba(255,255,255,200);"
                "color:rgba(0,0,0,200);"
                "}");

    ui->pushButton_5->setStyleSheet(

                "QPushButton{"
                "background-color:rgb(0, 0, 0);"
                "border-style:inset;"
                "border-width:2px;"
                "border-radius:10px;"
                "border-color:rgba(255,255,255,30);"
                "font:bold;"
                "color:white;"
                "padding:2px;"
                "}"

                "QPushButton:pressed{"
                "background-color:rgba(100,255,100,200);"
                "border-color:rgba(255,255,255,30);"
                "border-style:inset;"
                "color:rgba(0,0,0,100);"
                "}"

                "QPushButton:hover{"
                "background-color:rgba(100,255,100,100);"
                "border-color:rgba(255,255,255,200);"
                "color:rgba(0,0,0,200);"
                "}");

    ui->comboBox->addItem("简单");
    ui->comboBox->addItem("中等");
    ui->comboBox->addItem("困难");
    ui->comboBox->addItem("地狱");
    ui->comboBox->setCurrentIndex(1);
    ui->comboBox->setStyleSheet(
                "QComboBox{"
                "background-color:rgb(0, 0, 0);"
                "border-style:inset;"
                "border-width:2px;"
                "border-radius:10px;"
                "border-color:rgba(255,255,255,30);"
                "font:bold;"
                "color:white;"
                "padding:2px;"
                "}"

                "QComboBox:hover{"
                "background-color:rgba(100,255,100,100);"
                "border-color:rgba(255,255,255,200);"
                "color:rgba(0,0,0,200);"
                "}"
                );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reshow()
{
    this->show();
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    cb = new ChessBoard();
    connect(cb, SIGNAL(sendsignal()), this, SLOT(reshow()));
    cb->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->hide();
    ai = new AI_search();
    ai->Depth = _Depth;
    connect(ai, SIGNAL(sendsignal()), this, SLOT(reshow()));
    ai->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton ret;
    ret = QMessageBox::question(NULL, "选择一方", "作为服务器？");
    bool isServer = false, isOk;
    if (ret == QMessageBox::Yes)
    {
        isServer = true;
        this->hide();
        o = new OnlineGame(isServer, "127.0.0.1");
        connect(o, SIGNAL(sendsignal()), this, SLOT(reshow()));
        o->show();
    }
    else
    {
        QString text = QInputDialog::getText(NULL, "客户端", "输入服务器地址", QLineEdit::Normal, "127.0.0.1", &isOk);
        if (isOk)
        {
            this->hide();
            o = new OnlineGame(isServer, text);
            connect(o, SIGNAL(sendsignal()), this, SLOT(reshow()));
            o->show();
        }
    }


}


void MainWindow::on_comboBox_activated(const QString &arg1)
{
    int idx = ui->comboBox->currentIndex();
    qDebug() << idx << ui->comboBox->currentText();
    switch (idx)
    {
    case 0:_Depth = 2;break;
    case 1:_Depth = 3;break;
    case 2:_Depth = 4;break;
    case 3:_Depth = 6;break;
    default:_Depth = 3;break;
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    h = new help();
    h->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    exit(0);
}
