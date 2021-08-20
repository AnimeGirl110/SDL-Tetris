#include "Block.hpp"
#include "Game.hpp"

Block::Block(Color &color, int size, Vec2 pos)
    : pos(pos), color(color), size(size)
{
}

void Block::Draw(SDL_Renderer *renderer)
{
  SDL_Rect rect{pos.col * size + 1, pos.row * size + 1, size - 2, size - 2};
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
  SDL_RenderFillRect(renderer, &rect);
}

bool Block::Drop(int direction, Game &game)
{
  pos.row += direction;
  bool result = game.GetBlock(pos.row, pos.col) != nullptr;
  return result;
}

bool Block::Move(int direction, Game &game)
{
  pos.col += direction;
  bool result = game.GetBlock(pos.row, pos.col) != nullptr;

  return result;
}

Block *Block::ReturnBlock()
{
  return this;
}