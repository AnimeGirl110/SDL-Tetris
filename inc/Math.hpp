#pragma once

namespace Math
{
};

class Random
{
public:
  static void Initialize();
  static float GetFloat();
  static float GetFloat(float min, float max);
  static int GetInt(int min, int max);
};