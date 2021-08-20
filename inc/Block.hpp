#pragma once
#include "Color.hpp"
#include "SDL.h"
#include "Vec2.hpp"

class Block
{
public:
  Block(Color &color, int size, Vec2 pos);

  void Draw(SDL_Renderer *renderer);
  bool Drop(int direction, class Game &game);
  bool Move(int direction, class Game &game);
  Block *ReturnBlock();

  Vec2 pos;

private:
  Color &color;
  int size;
};
