#ifndef AI_SEARCH_H
#define AI_SEARCH_H
#include <QMouseEvent>
#include <QVector>
#include <QList>
#include <QMap>
#include <QPainter>
#include <algorithm>
#include "move.h"
#include "chessboard.h"
class AI_search : public ChessBoard
{
    Q_OBJECT
public:
    AI_search();
    QVector<Move> getAllPossibleMoves(int level);
    void getBestMove();
    int minMax(int level, QVector<Move> &tryMove);
    int getScore(int level);
    double evaluation(int level);
    double alphaBeta(int alpha, int beta, int level);
    double alphaBeta_multiThread(int alpha, int beta, int level);
    int pieceNum();
    void aiMove(bool isBlack);
    virtual void mouseReleaseEvent(QMouseEvent *ev);
//    virtual void paintEvent(QPaintEvent *e);
public:
//    QVector<Move> allMoves;
    QMap<QString, int> score;
    QMap<QString, QVector<int>> position;
    ChessPiece bak_pieces[32];
    ChessPiece bak[10][32];
    Move bestMove;
    int Depth;
private slots:
    void insteadOfHuman();
};

#endif // AI_SEARCH_H
