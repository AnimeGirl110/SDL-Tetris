#include <vector>
#include "Color.hpp"
#include "PieceYellow.hpp"

PieceYellow::PieceYellow(int size, Vec2 pos)
    : Piece(2, 2), size(size), pos(pos)
{
  blocks.emplace_back(new std::vector<Block *>);
  blocks.emplace_back(new std::vector<Block *>);

  blocks[0]->emplace_back(new Block{Color::yellow, size, Vec2{pos.row, pos.col}});
  blocks[0]->emplace_back(new Block{Color::yellow, size, Vec2{pos.row, pos.col + 1}});
  blocks[1]->emplace_back(new Block{Color::yellow, size, Vec2{pos.row + 1, pos.col}});
  blocks[1]->emplace_back(new Block{Color::yellow, size, Vec2{pos.row + 1, pos.col + 1}});
}
