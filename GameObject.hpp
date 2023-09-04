#pragma once
#include "Game.hpp"

class GameObject {
public:
  GameObject(const char *textureSheet, uint8_t x, uint8_t y);
  ~GameObject();
  void Update();
  void Render();

private:
  uint8_t xpos;
  uint8_t ypos;

  SDL_Texture *objTexture;
  SDL_Rect srcRect, destRect;
};
