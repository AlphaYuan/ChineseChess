#include "ai_search.h"
#include <QVector>
#include <QList>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QMap>
#include <qglobal.h>
#include <algorithm>
#include <random>
#include <time.h>
#include <QTimer>
#include <windows.h>
#include "move.h"
#include "dialog.h"
#include <QPushButton>
#include <QWidget>
#include <QThread>
AI_search::AI_search()
{
    this->setWindowTitle("中国象棋");
    bt2 = new QPushButton;
    bt2->setParent(this);
    bt2->setText("电脑");
    bt2->setVisible(true);
    bt2->setStyleSheet(
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
    bt2->setGeometry(0, 0, 100, 40);
    bt2->move(this->width * ratio + 20, this->height * ratio / 2 - 60);
    connect(bt2, SIGNAL(clicked()), this, SLOT(insteadOfHuman()));


    score["Zu"] = 30;
    score["Che"] = 620;
    score["Ma"] = 260;
    score["Pao"] = 380;
    score["Shi"] = 120;
    score["Xiang"] = 120;
    score["Shuai"] = 100000;

    position["Zu"] = QVector<int>({0, 0, 0, 0, 2, 6, 10, 14, 18, 0,
                                 0, 0, 0, 0, 0, 12, 20, 26, 36, 3,
                                 0, 0, 0, -2, 8, 18, 30, 42, 56, 6,
                                 0, 0, 0, 0, 0, 18, 34, 60, 80, 9,
                                 0, 0, 0, 4, 8, 20, 40, 80, 120, 12,
                                 0, 0, 0, 0, 0, 18, 34, 60, 80, 9,
                                 0, 0, 0, -2, 8, 18, 30, 42, 56, 6,
                                 0, 0, 0, 0, 0, 12, 20, 26, 36, 3,
                                 0, 0, 0, 0, 2, 6, 10, 14, 18, 0});
    position["Che"] = QVector<int>({-2, 8, 4, 6, 12, 12, 12, 12, 16, 14,
                                   10, 4, 8, 10, 16, 14, 18, 12, 20, 14,
                                   6, 8, 6, 8, 14, 12, 16, 12, 18, 12,
                                   14, 16, 14, 14, 20, 18, 22, 18, 24, 18,
                                   12, 8, 12, 14, 20, 18, 22, 18, 26, 16,
                                   14, 16, 14, 14, 20, 18, 22, 18, 24, 18,
                                   6, 8, 6, 8, 14, 12, 16, 12, 18, 12,
                                   10, 4, 8, 10, 16, 14, 18, 12, 20, 14,
                                   -2, 8, 4, 6, 12, 12, 12, 12, 16, 14});
    position["Ma"] = QVector<int>({0, 0, 4, 2, 4, 6, 8, 12, 4, 4,
                                  -4, 2, 2, 6, 12, 16, 24, 14, 10, 8,
                                  0, 4, 8, 8, 16, 14, 18, 16, 28, 16,
                                  0, 4, 8, 6, 14, 18, 24, 20, 16, 12,
                                  0, -2, 4, 10, 12, 16, 20, 18, 8, 4,
                                  0, 4, 8, 6, 14, 18, 24, 20, 16, 12,
                                  0, 4, 8, 8, 16, 14, 18, 16, 28, 16,
                                  -4, 2, 2, 6, 12, 16, 24, 14, 10, 8,
                                  0, 0, 4, 2, 4, 6, 8, 12, 4, 4});
    position["Xiang"] = QVector<int>({0, 0, -4, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, -4, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 8, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, -4, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, -4, 0, 0, 0, 0, 0, 0, 0});
    position["Shi"] = QVector<int>({0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, -4, 0, 0, 0, 0, 0, 0, 0,
                                    0, 8, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, -4, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    position["Shuai"] = QVector<int>({0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      -2, -4, -6, 0, 0, 0, 0, 0, 0, 0,
                                      0, -2, -4, 0, 0, 0, 0, 0, 0, 0,
                                      -2, -4, -6, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    position["Pao"] = QVector<int>({0, 0, 4, 0, -2, 0, 0, 2, 2, 6,
                                    0, 2, 0, 0, 0, 0, 0, 2, 2, 4,
                                    2, 4, 8, 0, 4, 0, -2, 0, 0, 0,
                                    6, 6, 6, 2, 2, 2, 4, -10, -4, -10,
                                    6, 6, 10, 4, 6, 8, 10, -8, -14, -12,
                                    6, 6, 6, 2, 2, 2, 4, -10, -4, -10,
                                    2, 4, 8, 0, 4, 0, -2, 0, 0, 0,
                                    0, 2, 0, 0, 0, 0, 0, 2, 2, 4,
                                    0, 0, 4, 0, -2, 0, 0, 2, 2, 6});
    for (int i = 0; i < 32; ++i)
        bak_pieces[i] = pieces[i];
    Depth = 4;
}

QVector<Move> AI_search::getAllPossibleMoves(int level)
{
    QVector<Move> allMoves;
    int m;
    if (level % 2)
        m = 16;
    else
        m = 0;
    for (int i = m; i < m + 16; ++i)
    {
        if (!pieces[i].isAlive)
            continue;
        for (int j = 0; j < 9; ++j)
        {
            for (int k = 0; k < 10; ++k)
            {
                if (canMove(pieces[i], j, k))
                {
                    allMoves.push_back(Move(pieces[i], j, k));
                }
            }
        }
    }
    return allMoves;
}

//void AI_search::getBestMove()
//{
//    int ans = 0, maxi = -10000;
//    QVector<Move> Moves = getAllPossibleMoves(true);
//    for (int i = 0; i < 32; ++i)
//        pieces[i] = bak_pieces[i];
//    for (QVector<Move>::iterator it = Moves.begin(); it != Moves.end(); ++it)
//    {
//        Move move = *it;
//        qDebug() << move.id << "," << move.to_x << "," << move.to_y;
//        canMove(pieces[move.id], move.to_x, move.to_y);
//        pieces[move.id].x = move.to_x;
//        pieces[move.id].y = move.to_y;
//        ans = getScore(1);
//        if (maxi < ans)
//        {
//            maxi = ans;
//            bestMove = move;
//            qDebug() << move.id << "," << move.to_x << "," << move.to_y;
//        }
//        for (int i = 0; i < 32; ++i)
//            pieces[i] = bak_pieces[i];
//    }
//    Moves.clear();
//    qDebug() << "ans:" << ans << "bestMove:" << bestMove.id << bestMove.to_x << bestMove.to_y;
//}

int AI_search::minMax(int level, QVector<Move> &tryMoves)
{

    if (level == Depth + 1)
    {
        return -1;
    }
    for (int z = 0; z < 32; ++z)
        bak[level][z] = pieces[z];
    int ans, maxi = -10000, idx = 0;
    tryMoves = getAllPossibleMoves(level);
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(tryMoves.begin(), tryMoves.end(), std::default_random_engine(seed));
    QVector<Move> newMoves;
    Move move, move1;
    for (int z = 0; z < 32; ++z)
        pieces[z] = bak[level][z];
    for (int i = 0; i < tryMoves.length(); ++i)
    {
        move = tryMoves[i];
        canMove(pieces[move.id], move.to_x, move.to_y);
        pieces[move.id].x = move.to_x;
        pieces[move.id].y = move.to_y;
        int j = minMax(level + 1, newMoves);
        if (j != -1)
        {
            move1 = newMoves[j];
            canMove(pieces[move1.id], move1.to_x, move1.to_y);
            pieces[move1.id].x = move1.to_x;
            pieces[move1.id].y = move1.to_y;
        }
        ans = getScore(level);
        if (maxi < ans)
        {
            maxi = ans;
            idx = i;
        }
        for (int z = 0; z < 32; ++z)
            pieces[z] = bak[level][z];
    }
    newMoves.clear();
    for (int z = 0; z < 32; ++z)
        pieces[z] = bak[level][z];
    return idx;
}

int AI_search::getScore(int level)
{
    int redScore = 0, blackScore = 0;
    for (int i = 0; i < 16; ++i)
    {
        if (pieces[i].isAlive)
            redScore += score[pieces[i].name];
    }
    for (int i = 16; i <32; ++i)
    {
        if (pieces[i].isAlive)
            blackScore += score[pieces[i].name];
    }
//    qDebug() << "score:" << redScore << "," << blackScore;
    if (level % 2)
        return blackScore - redScore;
    else
        return redScore - blackScore;
}


double AI_search::alphaBeta(int alpha_, int beta, int level)
{
    if (level == Depth + 1 || !pieces[20].isAlive || !pieces[4].isAlive)
    {
        return evaluation(level - 1);
    }
    for (int z = 0; z < 32; ++z)
        bak[level][z] = pieces[z];
    int value, i, alpha = alpha_;
    Move move1, move2;
    QVector<Move> allMoves = getAllPossibleMoves(level);
//    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
//    std::shuffle(allMoves.begin(), allMoves.end(), std::default_random_engine(seed));

    for (i = 0; i < allMoves.length(); ++i)
    {
        move1 = allMoves[i];
        movePiece(pieces[move1.id], move1.to_x, move1.to_y, false);
        value = -alphaBeta(-beta, -alpha, level + 1);
        for (int z = 0; z < 32; ++z)
            pieces[z] = bak[level][z];
        if (value >= beta)
            return beta;
        if (value > alpha)
        {
            alpha = value;
            if (level == 1)
                bestMove = move1;
        }
    }
    return alpha;
}

double AI_search::alphaBeta_multiThread(int alpha_, int beta, int level)
{
    if (level == Depth + 1 || !pieces[20].isAlive || !pieces[4].isAlive)
    {
        return evaluation(level - 1);
    }
    for (int z = 0; z < 32; ++z)
        bak[level][z] = pieces[z];
    int value, i, alpha = alpha_;
    Move move1, move2;
    QVector<Move> allMoves = getAllPossibleMoves(level);
//    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
//    std::shuffle(allMoves.begin(), allMoves.end(), std::default_random_engine(seed));

    for (i = 0; i < allMoves.length(); ++i)
    {
        move1 = allMoves[i];
        movePiece(pieces[move1.id], move1.to_x, move1.to_y, false);
//        if (level == 2)
//        {

//        }
        value = -alphaBeta(-beta, -alpha, level + 1);
        for (int z = 0; z < 32; ++z)
            pieces[z] = bak[level][z];
        if (value >= beta)
            return beta;
        if (value > alpha)
        {
            alpha = value;
            if (level == 1)
                bestMove = move1;
        }
    }
    return alpha;
}

double AI_search::evaluation(int level)
{
    double redScore = 0, blackScore = 0;
    int i;
    for (i = 0; i < 16; ++i)
        if (pieces[i].isAlive)
            redScore = redScore + score[pieces[i].name] * fmin(2.0, 32.0/pieceNum()) + position[pieces[i].name][10*pieces[i].x+pieces[i].y] * fmax(0.5, pieceNum()/32.0);
    for (; i < 32; ++i)
        if (pieces[i].isAlive)
            blackScore = blackScore + score[pieces[i].name] * fmin(2.0, 32.0/pieceNum()) + position[pieces[i].name][10*pieces[i].x+pieces[i].y] * fmax(0.5, pieceNum()/32.0);
    return blackScore - redScore;
}

int AI_search::pieceNum()
{
    int count = 0;
    for (int i = 0; i < 32; ++i)
        if (pieces[i].isAlive)
            count++;
    return count;
}

void AI_search::mouseReleaseEvent(QMouseEvent *ev)
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
            redTurn = !redTurn;
            if (judgeAttackKing())
            {
                sound4->play();
            }
        }
        selectedId = -1;
    }
    for (int i = 0; i < 32; ++i)
        bak_pieces[i] = pieces[i];
    repaint();
    if (!pieces[20].isAlive)
    {
        qDebug() << "Red wins!";
        Dialog w;
        w.setText("Red wins!");
        w.exec();
    }
    if (!redTurn)
    {
        aiMove(!redTurn);
        update();
        if (judgeAttackKing())
        {
            sound4->play();
        }
        if (!pieces[4].isAlive)
        {
            qDebug() << "Black wins!";
            Dialog w;
            w.setText("Black wins");
            w.exec();
        }
    }
}

void AI_search::aiMove(bool isBlack)
{
    if (pieceNum() < 16)
        Depth = 5;
    if (pieceNum() < 8)
        Depth = 5;
    clock_t start = clock();
    int alpha;
    if (isBlack)
        alpha = alphaBeta(-1000000, 1000000, 1);
    else
    {
        alpha = alphaBeta(-1000000, 1000000, 0);
    }
    qDebug() << pieces[bestMove.id].name << bestMove.to_x << bestMove.to_y << "alpha:" << alpha << "time:" << (clock() - start) / 1000.0 << "s";
    movePiece(pieces[bestMove.id], bestMove.to_x, bestMove.to_y, true);
    redTurn = !redTurn;
    for (int i = 0; i < 32; ++i)
        bak_pieces[i] = pieces[i];
}

void AI_search::insteadOfHuman()
{
    aiMove(false);
    update();
    qDebug() << redTurn;
    if (!redTurn)
    {
        aiMove(true);
        update();
        if (!pieces[4].isAlive)
        {
            qDebug() << "Black wins!";
            Dialog w;
            w.setText("Black wins");
            w.exec();
        }
    }
}
