#pragma once
#include "Piece.hpp"
#include "Vec2.hpp"

class PieceRed : public Piece
{
public:
  PieceRed(int size, Vec2 pos);

private:
  int size;
  Vec2 pos;
};
