#include "TextureManager.hpp"
#include "Game.hpp"

std::unordered_map<std::string, SDL_Texture *> TextureManager::textures;

SDL_Texture *TextureManager::LoadTexture(const std::string relativeFilePath) {
  if (textures.find(relativeFilePath) == textures.end()) {
    SDL_Surface *tmpSurface = IMG_Load(relativeFilePath.c_str());
    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    textures.emplace(relativeFilePath, texture);
    return texture;
  } else {
    return textures.at(relativeFilePath);
  }
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest,
                          SDL_RendererFlip spriteFlip) {
  SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, 0.0f, nullptr, spriteFlip);
}
