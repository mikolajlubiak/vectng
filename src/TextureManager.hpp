#pragma once
#include <SDL2/SDL.h>
#include <string>

class TextureManager {
public:
  static SDL_Texture *LoadTexture(const std::string relativeFilePath);
  static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);
};
