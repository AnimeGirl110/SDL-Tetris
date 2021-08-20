#include "Piece.hpp"
#include "Game.hpp"

Piece::Piece(int numRows, int numCols)
    : numRows(numRows), numCols(numCols)
{
}

void Piece::Draw(SDL_Renderer *renderer) const
{
  for (int row = 0; row < numRows; ++row)
  {
    for (int col = 0; col < numCols; ++col)
    {
      Block *block = blocks[row]->at(col);
      if (block)
      {
        block->Draw(renderer);
      }
    }
  }
}

bool Piece::Drop(int direction, Game &game)
{
  bool result = false;
  for (int row = 0; row < numRows; ++row)
  {
    for (int col = 0; col < numCols; ++col)
    {
      Block *block = blocks[row]->at(col);
      if (block)
      {

        result = block->Drop(direction, game) || result;
      }
    }
  }
  return result;
}

void Piece::Rotate()
{

  for (int row = 0; row < numRows; row++)
  {
    for (int col = 0; col < numCols; col++)
    {
      Block *block = blocks[row]->at(col);
      //this will mirror the block I think
      rotatedBlocks[col]->emplace_back(block);
    }
  }
}

bool Piece::Move(int direction, Game &game)
{
  bool result = false;
  for (int row = 0; row < numRows; ++row)
  {
    for (int col = 0; col < numCols; ++col)
    {
      Block *block = blocks[row]->at(col);
      if (block)
      {
        result = block->Move(direction, game) || result;
      }
    }
  }
  return result;
}

Block *Piece::GetBlock(int x, int y)
{
  Block *block = blocks[x]->at(y)->ReturnBlock();
  return block;
}