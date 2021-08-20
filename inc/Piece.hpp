#pragma once
#include <vector>
#include "Block.hpp"
#include "SDL.h"

class Piece
{
public:
  Piece(int numRows, int numCols);

  void Draw(SDL_Renderer *renderer) const;
  bool Drop(int direction, class Game &game);
  void Rotate();
  bool Move(int direction, class Game &game);
  Block *GetBlock(int x, int y);

  int numRows = 0;
  int numCols = 0;

protected:
  std::vector<std::vector<Block *> *> blocks;
  std::vector<std::vector<Block *> *> rotatedBlocks;
};
