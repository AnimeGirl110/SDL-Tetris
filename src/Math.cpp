#include "Math.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>

void Random::Initialize()
{
  srand(time(NULL));
}

float Random::GetFloat()
{
  return rand() / (float)(RAND_MAX);
}

float Random::GetFloat(float min, float max)
{
  return min + GetFloat() * (max - min);
}

int Random::GetInt(int min, int max)
{
  int r = min + (int)(GetFloat() * (1 + max - min));
  // std::cout << r << std::endl;
  return r;
}