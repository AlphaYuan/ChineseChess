#include "move.h"

Move::Move()
{

}

Move::Move(ChessPiece piece, int to_x, int to_y)
{
    this->piece = piece;
    this->to_x = to_x;
    this->to_y = to_y;
    id = piece.id;
    from_x = piece.x;
    from_y = piece.y;
}

Move::Move(int id, int from_x, int from_y, int to_x, int to_y)
{
    this->id = id;
    this->from_x = from_x;
    this->from_y = from_y;
    this->to_x = to_x;
    this->to_y = to_y;
}

Move::Move(int id, int from_x, int from_y, int to_x, int to_y, int killId)
{
    this->id = id;
    this->from_x = from_x;
    this->from_y = from_y;
    this->to_x = to_x;
    this->to_y = to_y;
    this->killedId = killId;
}
