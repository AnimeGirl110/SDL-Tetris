#pragma once
#include "Piece.hpp"
#include "Vec2.hpp"

class PieceMagenta : public Piece
{
public:
  PieceMagenta(int size, Vec2 pos);

private:
  int size;
  Vec2 pos;
};
