#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ai_search.h"
#include "chessboard.h"
#include "onlinegame.h"
#include <QMenu>
#include "help.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void reshow();


    void on_comboBox_activated(const QString &arg1);


    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    int _Depth = 2;
    ChessBoard* cb;
    AI_search* ai;
    OnlineGame* o;
    help* h;
};

#endif // MAINWINDOW_H
