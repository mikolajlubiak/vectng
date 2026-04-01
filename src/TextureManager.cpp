#include "TextureManager.hpp"
#include "Game.hpp"
#include <iostream>

std::unordered_map<std::string, SDL_Texture *> TextureManager::textures;

SDL_Texture *
TextureManager::LoadTexture(const std::string &relativeFilePath) {
  auto it = textures.find(relativeFilePath);
  if (it != textures.end()) {
    return it->second;
  }

  SDL_Surface *tmpSurface = IMG_Load(relativeFilePath.c_str());
  if (!tmpSurface) {
    std::cerr << "Error: Failed to load image '" << relativeFilePath
              << "': " << IMG_GetError() << std::endl;
    return nullptr;
  }

  SDL_Texture *texture =
      SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
  SDL_FreeSurface(tmpSurface);

  if (!texture) {
    std::cerr << "Error: Failed to create texture from '" << relativeFilePath
              << "': " << SDL_GetError() << std::endl;
    return nullptr;
  }

  textures.emplace(relativeFilePath, texture);
  return texture;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest,
                          SDL_RendererFlip spriteFlip) {
  SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, 0.0, nullptr, spriteFlip);
}

void TextureManager::Cleanup() {
  for (auto &[path, texture] : textures) {
    if (texture) {
      SDL_DestroyTexture(texture);
    }
  }
  textures.clear();
}
