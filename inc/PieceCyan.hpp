#pragma once
#include "Piece.hpp"
#include "Vec2.hpp"

class PieceCyan : public Piece
{
public:
  PieceCyan(int size, Vec2 pos);

private:
  int size;
  Vec2 pos;
};
