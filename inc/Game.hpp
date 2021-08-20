#pragma once
#include "Block.hpp"
#include "Config.hpp"
#include "Color.hpp"
#include "Piece.hpp"
#include "SDL.h"

class Game
{
public:
  Game();
  ~Game();
  Block *GetBlock(int row, int col);
  void SetBlock(int row, int col, Block *block);

private:
  bool Initialize();
  void LoadData();
  void Run();
  void RunController();
  void RunModel();
  void RunView();
  void UnloadData();
  void MakeSequence();
  void Check();
  void Move(int direction);
  void Drop(int direction);

  Block *blocks[Config::numBoardRows][Config::numBoardCols];
  int blockSize = 0;
  Uint32 fallDelayFast = Config::fallDelayFast;
  Uint32 fallDelayRegular = Config::fallDelayRegular;
  bool isDropping = false;
  bool isRunning = true;
  bool canMove = true;
  int numBoardCols = Config::numBoardCols;
  int numBoardRows = Config::numBoardRows;
  int numDisplayCols = Config::numDisplayCols;
  int numDisplayRows = Config::numDisplayRows;
  Piece *piece = nullptr;
  SDL_Renderer *renderer = nullptr;
  Uint32 timeDelayed = 0;
  Uint32 timePrior = 0;
  Uint32 moveDelay = 0;
  Color &wallColor = Color::gray;
  SDL_Window *window = nullptr;
  int windowHeight = 0;
  int windowWidth = 0;
  int score = 0;
};
