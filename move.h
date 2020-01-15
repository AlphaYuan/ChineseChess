#ifndef MOVE_H
#define MOVE_H
#include "chesspiece.h"

class Move
{
public:
    Move();
    Move(ChessPiece piece, int to_x, int to_y);
    Move(int id, int from_x, int from_y, int to_x, int to_y);
    Move(int id, int from_x, int from_y, int to_x, int to_y, int killId);
public:
    ChessPiece piece;
    int id;
    int from_x;
    int to_x;
    int from_y;
    int to_y;
    int killedId;
};

#endif // MOVE_H
