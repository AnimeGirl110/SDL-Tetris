#include <vector>
#include "Color.hpp"
#include "PieceRed.hpp"

PieceRed::PieceRed(int size, Vec2 pos)
    : Piece(2, 3), size(size), pos(pos)
{
  blocks.emplace_back(new std::vector<Block *>);
  blocks.emplace_back(new std::vector<Block *>);

  blocks[0]->emplace_back(new Block{Color::red, size, Vec2{pos.row, pos.col}});
  blocks[0]->emplace_back(new Block{Color::red, size, Vec2{pos.row, pos.col + 1}});
  blocks[0]->emplace_back(nullptr);
  blocks[1]->emplace_back(nullptr);
  blocks[1]->emplace_back(new Block{Color::red, size, Vec2{pos.row + 1, pos.col + 1}});
  blocks[1]->emplace_back(new Block{Color::red, size, Vec2{pos.row + 1, pos.col + 2}});
}
