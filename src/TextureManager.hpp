#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

class TextureManager {
public:
  static std::unordered_map<std::string, SDL_Texture *> textures;

  static SDL_Texture *LoadTexture(const std::string relativeFilePath);
  static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest,
                   SDL_RendererFlip spriteFlip);
};
