#include "onlinegame.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include "dialog.h"
#include <QMouseEvent>
OnlineGame::OnlineGame(bool isServer, QString addr)
{
    server = NULL;
    socket = NULL;

    if (isServer)
    {
        this->setWindowTitle("Server");
        server = new QTcpServer(this);
        server->listen(QHostAddress::Any, 8888);
        connect(server, SIGNAL(newConnection()), this, SLOT(startNewConnection()));
    }
    else
    {
        this->setWindowTitle("Client");
        socket = new QTcpSocket(this);
        socket->connectToHost(QHostAddress(addr), 8888);
        connect(socket, SIGNAL(readyRead()), this, SLOT(recv()));
    }
}

OnlineGame::~OnlineGame()
{

}

void OnlineGame::withdrawOneStep()
{
    withdraw();
    char a[2];
    a[0] = 3;
    socket->write(a, 2);
    update();
}

void OnlineGame::recv()
{
    QByteArray ba = socket->readAll();
    char cmd = ba[0];
    if (cmd == 1)
    {
        int data = ba[1];
        init(data == 1);
        side = (data == 1);
        redSide = (data == 1);
        redTurn = !redTurn;
    }
    if (cmd == 2)
    {
        int id = ba[1];
        int to_x = ba[2];
        int to_y = ba[3];
        movePiece(pieces[id], to_x, to_y, true);
        update();
        if (!pieces[20].isAlive)
        {
            qDebug() << "Red wins!";
            Dialog w;
            w.setText("Red wins!");
            w.exec();
        }
        if (!pieces[4].isAlive)
        {
            qDebug() << "Black wins!";
            Dialog w;
            w.setText("Black wins!");
            w.exec();
        }
        redTurn = !redTurn;
        side = true;
    }
    if (cmd == 3)
    {
        withdraw();
        update();
    }
}

void OnlineGame::mouseReleaseEvent(QMouseEvent *ev)
{
    if (side == false)
        return;
    point = ev->pos();
    QPoint cPoint = center(point.x(), point.y());
    if (cPoint.x() == -1 || cPoint.y() == -1)
        return;
    int click = getPiece(point.x(), point.y());
    if (selectedId == -1)
    {
        if (click != -1 && redTurn == pieces[click].isRed)
        {
            selectedId = click;
        }
    }
    else
    {
        if (redTurn == pieces[selectedId].isRed && canMove(pieces[selectedId], cPoint.x(), cPoint.y()))
        {
            movePiece(pieces[selectedId], cPoint.x(), cPoint.y(), true);
            char a[6];
            a[0] = 2;
            a[1] = selectedId;
            a[2] = 8 - cPoint.x();
            a[3] = 9 - cPoint.y();
            socket->write(a, 4);
            redTurn = !redTurn;
            side = false;
        }
        selectedId = -1;
    }
    update();
    if (!pieces[20].isAlive)
    {
        qDebug() << "Red wins!";
        Dialog w;
        w.setText("红方获胜!");
        w.exec();
    }
    if (!pieces[4].isAlive)
    {
        qDebug() << "Black wins!";
        Dialog w;
        w.setText("黑方获胜!");
        w.exec();
    }
}

void OnlineGame::startNewConnection()
{
    if (socket)
        return;
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(recv()));
    char a[2];
    a[0] = 1;
    a[1] = 0;
    init(a[1] == 0);
    side = (a[1] == 0);
    socket->write(a, 2);
    redSide = (a[1] == 0);
}
