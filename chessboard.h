#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QMouseEvent>
#include <QStack>
#include "chesspiece.h"
#include "move.h"
#include <QPixmap>
#include <QDesktopWidget>
#include <QPushButton>
#include <QSound>
#include <QSoundEffect>
#include <QTimer>
class ChessBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoard(QWidget *parent = nullptr);

    void init(bool red);

    QPoint realCoord(QPoint point);
    QPoint boardCoord(QPoint point);

    int getPiece(int x, int y);
    int getPieceBoard(int x, int y);

    bool canMove(ChessPiece move, int to_x, int to_y);
    bool canMoveZu(ChessPiece move, int to_x, int to_y);
    bool canMoveMa(ChessPiece move, int to_x, int to_y);
    bool canMoveChe(ChessPiece move, int to_x, int to_y);
    bool canMovePao(ChessPiece move, int to_x, int to_y);
    bool canMoveXiang(ChessPiece move, int to_x, int to_y);
    bool canMoveShi(ChessPiece move, int to_x, int to_y);
    bool canMoveShuai(ChessPiece move, int to_x, int to_y);

    void movePiece(ChessPiece piece, int to_x, int to_y, bool trueMove);
    void saveSteps(ChessPiece piece, int to_x, int to_y, int killId);
    void withdraw();

    bool judgeAttackKing();

    QPoint center(int x, int y);
    QPoint center(ChessPiece piece);

    void paintEvent(QPaintEvent *e);
    void drawPiece(QPainter &painter, ChessPiece piece);
    virtual void mouseReleaseEvent(QMouseEvent *ev);
public:
    int width;
    int height;
    double ratio;
    int r;
    int selectedId;
    bool redSide;
    bool redTurn;
    ChessPiece pieces[32], selectedPiece;
    QPixmap board, bg;
    QStack<Move> steps;
    QPoint point;
    QPushButton *bt1, *bt2, *bt3;
    QSound *sound1, *sound2, *sound3, *sound4;
    QSoundEffect *sEffect1;
    QTimer *timer;
signals:
    void sendsignal();

public slots:
    void withdrawOneStep();
    void returnToMain();
};

#endif // CHESSBOARD_H
