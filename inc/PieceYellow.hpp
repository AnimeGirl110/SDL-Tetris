#pragma once
#include "Piece.hpp"
#include "Vec2.hpp"

class PieceYellow : public Piece
{
public:
  PieceYellow(int size, Vec2 pos);

private:
  int size;
  Vec2 pos;
};
