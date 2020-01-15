#include "chessboard.h"
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QtMath>
#include "dialog.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QIcon>
#include "move.h"
#include <QPushButton>
#include <QSound>
#include <QSoundEffect>
#include "mainwindow.h"
ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
{
    this->setWindowIcon(QIcon("logo.ico"));
    this->setObjectName("ChessBoard");
//    this->setStyleSheet("#ChessBoard{background-image:u/rl(:/img/images/pure.jpg);}");
    bt1 = NULL;
    bt2 = NULL;
    bt3 = NULL;
    init(true);
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - this->geometry().width()) / 2, (desktop->height() - this->geometry().width()) / 2);
}

void ChessBoard::init(bool Red)
{
    width = 442;
    height = 492;
    ratio = 1.75;
    this->setGeometry(0, 0, (width + 150) * ratio, height * ratio);

    bt1 = new QPushButton;
    bt1->setParent(this);
    bt1->setText("悔棋");
    bt1->setVisible(true);
    bt1->setStyleSheet(
                "QPushButton{"
                "background-color:rgb(14, 255, 120);"
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
    bt1->setGeometry(0, 0, 100, 40);
    bt1->move(this->width * ratio + 20, this->height * ratio / 2);
    connect(bt1, SIGNAL(clicked()), this, SLOT(withdrawOneStep()));

    bt3 = new QPushButton;
    bt3->setParent(this);
    bt3->setText("返回主页");
    bt3->setVisible(true);
    bt3->setStyleSheet(
                "QPushButton{"
                "background-color:rgb(14, 255, 120);"
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
    bt3->setGeometry(0, 0, 100, 40);
    bt3->move(this->width * ratio + 20, this->height * ratio / 2 + 60);
    connect(bt3, SIGNAL(clicked()), this, SLOT(returnToMain()));

    sound1 = new QSound(":/sound/sounds/sound1.wav");
    sound2 = new QSound(":/sound/sounds/eat.wav");
    sound3 = new QSound(":/sound/sounds/Choose.wav");
    sound4 = new QSound(":/sound/sounds/AttackKing.wav");
    board = QPixmap(":/img/images/bg.bmp");
    bg = QPixmap(":/img/images/bg1.jpg");
    redTurn = Red;
    redSide = true;
    r = 20 * ratio;
    selectedId = -1;
    bool isRed = true;

    pieces[0] = Che(0, 0, isRed, 0);
    pieces[1] = Ma(1, 0, isRed, 1);
    pieces[2] = Xiang(2, 0, isRed, 2);
    pieces[3] = Shi(3, 0, isRed, 3);
    pieces[4] = Shuai(4, 0, isRed, 4);
    pieces[5] = Shi(5, 0, isRed, 5);
    pieces[6] = Xiang(6, 0, isRed, 6);
    pieces[7] = Ma(7, 0, isRed, 7);
    pieces[8] = Che(8, 0, isRed, 8);
    pieces[9] = Pao(1, 2, isRed, 9);
    pieces[10] = Pao(7, 2, isRed, 10);
    pieces[11] = Zu(0, 3, isRed, 11);
    pieces[12] = Zu(2, 3, isRed, 12);
    pieces[13] = Zu(4, 3, isRed, 13);
    pieces[14] = Zu(6, 3, isRed, 14);
    pieces[15] = Zu(8, 3,isRed, 15);

    pieces[16] = Che(0, 9, !isRed, 16);
    pieces[17] = Ma(1, 9, !isRed, 17);
    pieces[18] = Xiang(2, 9, !isRed, 18);
    pieces[19] = Shi(3, 9, !isRed, 19);
    pieces[20] = Shuai(4, 9, !isRed, 20);
    pieces[21] = Shi(5, 9, !isRed, 21);
    pieces[22] = Xiang(6, 9, !isRed, 22);
    pieces[23] = Ma(7, 9, !isRed, 23);
    pieces[24] = Che(8, 9, !isRed, 24);
    pieces[25] = Pao(1, 7, !isRed, 25);
    pieces[26] = Pao(7, 7, !isRed, 26);
    pieces[27] = Zu(0, 6, !isRed, 27);
    pieces[28] = Zu(2, 6, !isRed, 28);
    pieces[29] = Zu(4, 6, !isRed, 29);
    pieces[30] = Zu(6, 6, !isRed, 30);
    pieces[31] = Zu(8, 6, !isRed, 31);
    if (!Red)
    for (int i = 0; i < 32; ++i)
    {
        pieces[i].x = 8 - pieces[i].x;
        pieces[i].y = 9 - pieces[i].y;
    }
}

void ChessBoard::paintEvent(QPaintEvent *e)
{
    ratio = fmin(this->geometry().width() / (double)width, this->geometry().height() / (double)height);
    r = 20 * ratio;
    bt1->move(this->width * ratio + 20, this->height * ratio / 2);
    if (bt2)
        bt2->move(this->width * ratio + 20, this->height * ratio / 2 - 60);
    bt3->move(this->width * ratio + 20, this->height * ratio / 2 + 60);
    QPainter painter(this);
    painter.drawPixmap(rect(), bg);
    painter.drawPixmap(QRect(0, 0, width * ratio, height * ratio), board);
    for (int i = 0; i < 32; ++i)
    {
        drawPiece(painter, pieces[i]);
    }
}

void ChessBoard::mouseReleaseEvent(QMouseEvent *ev)
{
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
            sound3->play();
        }
    }
    else
    {
        if (redTurn == pieces[selectedId].isRed && canMove(pieces[selectedId], cPoint.x(), cPoint.y()))
        {
            movePiece(pieces[selectedId], cPoint.x(), cPoint.y(), true);
            if (judgeAttackKing())
            {
                sound4->play();
            }
            redTurn = !redTurn;
        }
        selectedId = -1;
    }
//    qDebug() << point << cPoint << click << selectedId;
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

QPoint ChessBoard::realCoord(QPoint point)
{
    return QPoint(24 * ratio + 49 * ratio * point.x(), ratio * (462 - 49 * point.y()));
}

QPoint ChessBoard::boardCoord(QPoint point)
{
    return QPoint(round((point.x() - 24.0 * ratio) / 49.0 / ratio), round((462.0 * ratio - point.y()) / 49.0 / ratio));
}

QPoint ChessBoard::center(int x, int y)
{
    int minx = -1, miny = -1;
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            QPoint rC = realCoord(QPoint(i, j));
            double tmp = pow(x - rC.x(), 2) + pow(y - rC.y(), 2);
            if (tmp < r * r)
            {
                minx = rC.x();
                miny = rC.y();
            }
        }
    }
    return boardCoord(QPoint(minx, miny));
}


int ChessBoard::getPiece(int rx, int ry)
{
    QPoint centerPoint = center(rx, ry);
//    qDebug() << centerPoint << endl;
    int i;
    for (i = 0; i < 32; ++i)
    {
        if (pieces[i].x == centerPoint.x() && pieces[i].y == centerPoint.y() && pieces[i].isAlive)
        {

            return i;
        }
    }
    return -1;
}

int ChessBoard::getPieceBoard(int x, int y)
{
    int i;
    for (i = 0; i < 32; ++i)
    {
        if (pieces[i].x == x && pieces[i].y == y && pieces[i].isAlive)
        {

            return i;
        }
    }
    return -1;
}

void ChessBoard::drawPiece(QPainter &painter, ChessPiece piece)
{
    if (piece.isAlive)
    {
        if (selectedId != piece.id)
            painter.drawPixmap(realCoord(QPoint(piece.x, piece.y)).x() - r, realCoord(QPoint(piece.x, piece.y)).y() - r, 2 * r, 2 * r, piece.picture);
        else
            painter.drawPixmap(realCoord(QPoint(piece.x, piece.y)).x() - r, realCoord(QPoint(piece.x, piece.y)).y() - r, 2 * r, 2 * r, piece.selectedPic);
    }
}

void ChessBoard::movePiece(ChessPiece piece, int to_x, int to_y, bool trueMove)
{
    int i = getPieceBoard(to_x, to_y);
    if (i != -1)
        pieces[i].isAlive = false;
    pieces[piece.id].x = to_x;
    pieces[piece.id].y = to_y;
    if (trueMove)
    {
        steps.push(Move(piece.id, piece.x, piece.y, to_x, to_y, i));
        if (i != -1)
            sound2->play();
        else
            sound1->play();
    }
//    sound1->play();
}

void ChessBoard::returnToMain()
{
    emit sendsignal();
    this->close();
}

void ChessBoard::withdrawOneStep()
{
    withdraw();
    update();
}

void ChessBoard::withdraw()
{
    if (steps.empty())
        return;
    redTurn = !redTurn;
    Move move = steps.top();
    steps.pop();
    if (move.killedId != -1)
        pieces[move.killedId].isAlive = true;
    pieces[move.id].x = move.from_x;
    pieces[move.id].y = move.from_y;
//    qDebug() << move.id << move.from_x << move.from_y << move.to_x << move.to_y << move.killedId << steps.size();
}

bool ChessBoard::canMove(ChessPiece move, int to_x, int to_y)
{
    if (move.name == "Zu")
        return canMoveZu(move, to_x, to_y);
    if (move.name == "Che")
        return canMoveChe(move, to_x, to_y);
    if (move.name == "Ma")
        return canMoveMa(move, to_x, to_y);
    if (move.name == "Xiang")
        return canMoveXiang(move, to_x, to_y);
    if (move.name == "Shi")
        return canMoveShi(move, to_x, to_y);
    if (move.name == "Shuai")
        return canMoveShuai(move, to_x, to_y);
    if (move.name == "Pao")
        return canMovePao(move, to_x, to_y);
    return false;
}

bool ChessBoard::canMoveZu(ChessPiece move, int to_x, int to_y)
{
    int dx = to_x - move.x, dy = to_y - move.y;
    if (abs(dx) + abs(dy) != 1)
        return false;
    if ((move.isRed == redSide && dy == -1) || (!move.isRed == redSide && dy == 1))
        return false;
    if (dy == 0)
    {
        if ((move.isRed == redSide && move.y < 5) || (!move.isRed == redSide && move.y >= 5))
                return false;
    }
    if (to_x < 0 || to_x > 8 || to_y < 0 || to_y > 9)
        return false;
    int i = getPieceBoard(to_x, to_y);
    if (i != -1)
    {
        if (move.isRed == pieces[i].isRed)
            return false;
        else {
//            pieces[i].isAlive = false;
            return true;
        }
    }
    return true;
}

bool ChessBoard::canMoveMa(ChessPiece move, int to_x, int to_y)
{
    int dx = to_x - move.x, dy = to_y - move.y, i;
    if (to_x < 0 || to_x > 8 || to_y < 0 || to_y > 9)
        return false;
    if (!((abs(dx) == 1 && abs(dy) == 2) || (abs(dx) == 2 && abs(dy) == 1)))
        return false;
    if (getPieceBoard(move.x + dx / 2, move.y + dy / 2) != -1)
        return false;
    else
    {
        i = getPieceBoard(to_x, to_y);
        if (i != -1)
        {
            if (pieces[i].isRed == move.isRed)
                return false;
//            else
//                pieces[i].isAlive = false;
        }
    }
    return true;
}

bool ChessBoard::canMoveShuai(ChessPiece move, int to_x, int to_y)
{
    int dx = to_x - move.x, dy = to_y - move.y;
    int i = getPieceBoard(to_x, to_y);
//    qDebug() << move.id << ", " << i;

    if (i != -1)
        if (move.isRed == pieces[i].isRed)
            return false;
    if ((move.isRed == redSide && to_y >= 0 && to_y <= 2 && to_x >= 3 && to_x <= 5) ||
        (!move.isRed == redSide && to_y >= 7 && to_y <= 9 && to_x >= 3 && to_x <= 5))
    {
        if (abs(dx) + abs(dy) == 1)
        {
//            if (i != -1)
//                pieces[i].isAlive = false;
            return true;
        }
    }
    if (dx == 0 && move.id != i)
    {
        if (i == 20)
        {
            for (int j = 1; j < dy; ++j)
                if (getPieceBoard(move.x, move.y + j) != -1)
                    return false;
//            pieces[i].isAlive = false;
            return true;
        }
        if (i == 4)
        {
            for (int j = -1; j > dy; --j)
                if (getPieceBoard(move.x, move.y + j) != -1)
                    return false;
//            pieces[i].isAlive = false;
            return true;
        }
    }
    return false;
}

bool ChessBoard::canMoveShi(ChessPiece move, int to_x, int to_y)
{
    int dx = to_x - move.x, dy = to_y - move.y;
    int i = getPieceBoard(to_x, to_y);
    if (i != -1 && move.isRed == pieces[i].isRed)
        return false;
    if ((move.isRed == redSide && to_y >= 0 && to_y <= 2 && to_x >= 3 && to_x <= 5) ||
        (move.isRed != redSide && to_y >= 7 && to_y <= 9 && to_x >= 3 && to_x <= 5))
    {
        if (abs(dx) == 1 && abs(dy) == 1)
        {
//            if (i != -1)
//                pieces[i].isAlive = false;
            return true;
        }
    }
    return false;
}

bool ChessBoard::canMoveXiang(ChessPiece move, int to_x, int to_y)
{
    int dx = to_x - move.x, dy = to_y - move.y;
    int i = getPieceBoard(to_x, to_y);
    if (i != -1 && move.isRed == pieces[i].isRed)
        return false;
    if (!(abs(dx) == 2 && abs(dy) == 2))
        return false;
    if (getPieceBoard(move.x + dx / 2, move.y + dy / 2) != -1)
        return false;
    if ((move.isRed == redSide && to_y >= 0 && to_y <= 4) ||
        (!move.isRed == redSide && to_y >= 5 && to_y <= 9))
    {
//        if (i != -1)
//            pieces[i].isAlive = false;
        return true;
    }
    return false;
}

bool ChessBoard::canMovePao(ChessPiece move, int to_x, int to_y)
{
    int dx = to_x - move.x, dy = to_y - move.y, count = 0;
    if (to_x < 0 || to_x > 8 || to_y < 0 || to_y > 9)
        return false;
    int i = getPieceBoard(to_x, to_y);
    if (i != -1 && move.isRed == pieces[i].isRed)
        return false;
    if (dx != 0 && dy != 0)
        return false;
    if (dx == 0)
    {
        if (dy > 0)
        {
            for (int j = 1; j < dy; ++j)
                if (getPieceBoard(move.x, move.y + j) != -1)
                    count++;
        }
        if (dy < 0)
        {
            for (int j = -1; j > dy; --j)
                if (getPieceBoard(move.x, move.y + j) != -1)
                    count++;
        }
    }
    if (dy == 0)
    {
        if (dx > 0)
        {
            for (int j = 1; j < dx; ++j)
                if (getPieceBoard(move.x + j, move.y) != -1)
                    count++;
        }
        if (dx < 0)
        {
            for (int j = -1; j > dx; --j)
                if (getPieceBoard(move.x + j, move.y) != -1)
                    count++;
        }
    }
    if (count == 0 && i == -1)
        return true;
    if (i != -1 && count == 1)
    {
//        pieces[i].isAlive = false;
        return true;
    }
    return false;
}

bool ChessBoard::canMoveChe(ChessPiece move, int to_x, int to_y)
{
    int dx = to_x - move.x, dy = to_y - move.y;
    if (to_x < 0 || to_x > 8 || to_y < 0 || to_y > 9)
        return false;
    int i = getPieceBoard(to_x, to_y);
    if (i != -1 && move.isRed == pieces[i].isRed)
        return false;
    if (dx != 0 && dy != 0)
        return false;
    if (dx == 0)
    {
        if (dy > 0)
        {
            for (int j = 1; j < dy; ++j)
            {
                if (getPieceBoard(move.x, move.y + j) != -1)
                    return false;
            }
//            if (i != -1)
//                pieces[i].isAlive = false;
            return true;
        }
        if (dy < 0)
        {
            for (int j = -1; j > dy; --j)
                if (getPieceBoard(move.x, move.y + j) != -1)
                    return false;
//            if (i != -1)
//                pieces[i].isAlive = false;
            return true;
        }
    }
    if (dy == 0)
    {
        if (dx > 0)
        {
            for (int j = 1; j < dx; ++j)
            {
                if (getPieceBoard(move.x + j, move.y) != -1)
                    return false;
            }
//            if (i != -1)
//                pieces[i].isAlive = false;
            return true;
        }
        if (dx < 0)
        {
            for (int j = -1; j > dx; --j)
                if (getPieceBoard(move.x + j, move.y) != -1)
                    return false;
//            if (i != -1)
//                pieces[i].isAlive = false;
            return true;
        }
    }
    return false;
}

bool ChessBoard::judgeAttackKing()
{
    for (int i = 0; i < 32; ++i)
    {
        if (!pieces[i].isAlive)
            continue;
        for (int j = 0; j < 9; ++j)
        {
            for (int k = 0; k < 10; ++k)
            {
                if (canMove(pieces[i], j, k))
                {
                    int m = getPieceBoard(j, k);
                    if (m == 4 || m == 20)
                    {
                        qDebug() << j << k;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
