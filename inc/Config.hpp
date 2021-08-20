#pragma once

struct Config
{
  static int const fallDelayFast = 250;    // milliseconds b/w falls
  static int const fallDelayRegular = 500; // milliseconds b/w falls
  static int const numBoardCols = 12;      // including walls
  static int const numBoardRows = 22;      // including walls
  static int const numDisplayCols = 6;
  static int const numDisplayRows = 4;
  inline static char const *title = "Tetris";
  static int const windowMaxHeight = 768;
  static int const windowMaxWidth = 1024;
};
