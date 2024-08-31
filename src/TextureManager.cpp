#include "TextureManager.hpp"
#include "Game.hpp"

SDL_Texture *TextureManager::LoadTexture(const std::string relativeFilePath) {
  SDL_Surface *tmpSurface = IMG_Load(relativeFilePath.c_str());
  SDL_Texture *texture =
      SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
  SDL_FreeSurface(tmpSurface);
  return texture;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest) {
  SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
