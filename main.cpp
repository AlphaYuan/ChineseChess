#include "mainwindow.h"
#include <QApplication>
#include "chessboard.h"
#include "ai_search.h"
#include "dialog.h"
#include "onlinegame.h"
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // human vs. human
//    ChessBoard w;
//    w.init(true);

    // human vs. ai
//    AI_search ai;
//    ai.show();

    // online game
//    QMessageBox::StandardButton ret;
//    ret = QMessageBox::question(NULL, "server or client?", "as a server");
//    bool isServer = false;
//    if (ret == QMessageBox::Yes)
//    {
//        isServer = true;
//    }
//    OnlineGame o(isServer);
//    o.show();

    MainWindow w;
    w.show();
    return a.exec();
}
