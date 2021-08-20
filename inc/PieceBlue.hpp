#pragma once
#include "Piece.hpp"
#include "Vec2.hpp"

class PieceBlue : public Piece
{
public:
  PieceBlue(int size, Vec2 pos);

private:
  int size;
  Vec2 pos;
};
