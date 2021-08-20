#include <algorithm>
#include <iostream>
#include "PieceCyan.hpp"
#include "PieceGreen.hpp"
#include "PieceMagenta.hpp"
#include "PieceRed.hpp"
#include "PieceYellow.hpp"
#include "PieceOrange.hpp"
#include "PieceBlue.hpp"
#include "Game.hpp"
#include "Vec2.hpp"
#include "Math.hpp"

using std::cout;
using std::endl;
using std::max;
using std::min;

Game::Game()
{
  cout << "Game::Game()" << endl;
  if (Initialize())
  {
    Run();
  }
}

Game::~Game()
{
  cout << "Game::~Game()" << endl;
  UnloadData();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool Game::Initialize()
{
  cout << "Game::Initialize()" << endl;

  Random::Initialize();

  int blockWidth = Config::windowMaxWidth / (numBoardCols + numDisplayCols);
  int blockHeight = Config::windowMaxHeight / max(numBoardRows, numDisplayRows);
  blockSize = min(blockWidth, blockHeight);
  windowWidth = blockSize * (numBoardCols + numDisplayCols);
  windowHeight = blockSize * max(numBoardRows, numDisplayRows);

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }

  window = SDL_CreateWindow(
      Config::title,
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      windowWidth, windowHeight,
      0);
  if (!window)
  {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  renderer = SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer)
  {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    return false;
  }

  // TODO: Random::Init();

  LoadData();

  timePrior = SDL_GetTicks();

  return true;
}

void Game::LoadData()
{
  cout << "Game::LoadData()" << endl;
  for (int row = 0; row < numBoardRows; ++row)
  {
    for (int col = 0; col < numBoardCols; ++col)
    {
      if (row == 0 || row == numBoardRows - 1 || col == 0 || col == numBoardCols - 1)
      {
        blocks[row][col] = new Block{wallColor, blockSize, Vec2{row, col}};
      }
      else
      {
        blocks[row][col] = nullptr;
      }
    }
  }
  MakeSequence();
}

void Game::Run()
{
  cout << "Game::Run()" << endl;
  while (isRunning)
  {
    RunController();
    RunModel();
    RunView();
  }
}

void Game::RunController()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      isRunning = false;
      break;
    }
  }

  const Uint8 *keyState = SDL_GetKeyboardState(NULL);
  if (keyState[SDL_SCANCODE_ESCAPE])
  {
    isRunning = false;
  }
  if (keyState[SDL_SCANCODE_A])
  {
    Move(-1);
  }
  if (keyState[SDL_SCANCODE_D])
  {
    Move(1);
  }
  isDropping = (keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN]);
  // TODO -- process other keypresses here
}

void Game::RunModel()
{

  while (!SDL_TICKS_PASSED(SDL_GetTicks(), timePrior + 16))
    ;
  Uint32 timeChange = SDL_GetTicks() - timePrior;
  if (timeChange > 50)
  {
    timeChange = 50;
  }
  timeDelayed += timeChange;
  Uint32 fallDelay = (isDropping ? fallDelayFast : fallDelayRegular);
  if (timeDelayed >= fallDelay)
  {
    Drop(1);
    timeDelayed -= fallDelay;
  }
  moveDelay += timeChange;
  if (moveDelay > 150)
  //TODO: Move the delay to config
  {
    canMove = true;
    moveDelay = 0;
  }
  timePrior = SDL_GetTicks();
}

void Game::RunView()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  for (int row = 0; row < numBoardRows; ++row)
  {
    for (int col = 0; col < numBoardCols; ++col)
    {
      Block *block = blocks[row][col];
      if (block)
      {

        block->Draw(renderer);
      }
    }
  }
  piece->Draw(renderer);

  SDL_RenderPresent(renderer);
}

void Game::UnloadData()
{
  cout << "Game::UnloadData()" << endl;
  // TODO
}

void Game::MakeSequence()
{
  int r = Random::GetInt(0, 6);
  switch (r)
  {
  case 0:
    piece = new PieceGreen(blockSize, Vec2{1, 1});
    return;
  case 1:
    piece = new PieceCyan(blockSize, Vec2{1, 1});
    return;
  case 2:
    piece = new PieceBlue(blockSize, Vec2{1, 1});
    return;
  case 3:
    piece = new PieceYellow(blockSize, Vec2{1, 1});
    return;
  case 4:
    piece = new PieceMagenta(blockSize, Vec2{1, 1});
    return;
  case 5:
    piece = new PieceRed(blockSize, Vec2{1, 1});
    return;
  case 6:
    piece = new PieceOrange(blockSize, Vec2{1, 1});
    return;
  }
}

void Game::Check()
{
  for (int row = 0; row < numBoardRows; row++)
  {
    for (int col = 0; col < numBoardCols; col++)
    {
      Block *block = blocks[row][col];
      if (!block)
      {
        //if there is no block, return
        return;
      }
    }
  }
  //Destroy(row);
  //add some number of points to score
}

Block *Game::GetBlock(int row, int col)
{
  return blocks[row][col];
}

void Game::SetBlock(int row, int col, Block *block)
{
  blocks[row][col] = block;
}

void Game::Move(int direction)
{
  if (canMove)
  {
    if (piece->Move(direction, *this))
    {
      piece->Move(-direction, *this);
    }
    canMove = false;
    moveDelay = 0;
  }
}

void Game::Drop(int direction)
{
  if (canMove)
  {
    if (piece->Drop(direction, *this))
    {
      piece->Drop(-direction, *this);
      for (int row = 0; row < piece->numRows; row++)
      {
        for (int col = 0; col < piece->numCols; col++)
        {
          if (Block *block = piece->GetBlock(row, col))
          {
            SetBlock(block->pos.row, block->pos.col, block);
          }
          //find blocks in piece, then see if they fit
        }
      }
      MakeSequence();
    }
    canMove = false;
    moveDelay = 0;
  }
}