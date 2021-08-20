#pragma once
#include "Piece.hpp"
#include "Vec2.hpp"

class PieceOrange : public Piece
{
public:
  PieceOrange(int size, Vec2 pos);

private:
  int size;
  Vec2 pos;
};
