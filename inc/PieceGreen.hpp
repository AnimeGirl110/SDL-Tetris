#pragma once
#include "Piece.hpp"
#include "Vec2.hpp"

class PieceGreen : public Piece
{
public:
  PieceGreen(int size, Vec2 pos);

private:
  int size;
  Vec2 pos;
};
