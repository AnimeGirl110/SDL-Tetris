#include <vector>
#include "Color.hpp"
#include "PieceCyan.hpp"

PieceCyan::PieceCyan(int size, Vec2 pos)
    : Piece(1, 4), size(size), pos(pos)
{
  blocks.emplace_back(new std::vector<Block *>);

  blocks[0]->emplace_back(new Block{Color::cyan, size, Vec2{pos.row, pos.col}});
  blocks[0]->emplace_back(new Block{Color::cyan, size, Vec2{pos.row, pos.col + 1}});
  blocks[0]->emplace_back(new Block{Color::cyan, size, Vec2{pos.row, pos.col + 2}});
  blocks[0]->emplace_back(new Block{Color::cyan, size, Vec2{pos.row, pos.col + 3}});
}
