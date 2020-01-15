#ifndef ONLINEGAME_H
#define ONLINEGAME_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>
#include "chessboard.h"
class OnlineGame : public ChessBoard
{
    Q_OBJECT
public:
    explicit OnlineGame(bool isServer, QString addr);
    ~OnlineGame();
    virtual void mouseReleaseEvent(QMouseEvent *ev);

private:
    QTcpServer* server;
    QTcpSocket* socket;
    bool side;

private slots:
    void startNewConnection();
    void recv();
    void withdrawOneStep();
};

#endif // ONLINEGAME_H
