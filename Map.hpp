#pragma once
#include "Game.hpp"

class Map {
public:
  Map();
  ~Map();

  void LoadMap(Uint8[32][32]);
  void DrawMap();

private:
  SDL_Rect src, dest;
  SDL_Texture *dirt;
  SDL_Texture *grass;
  SDL_Texture *water;
  Uint8 map[32][32];
};
