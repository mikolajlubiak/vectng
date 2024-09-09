#pragma once

#include "Components.hpp"
#include <SDL2/SDL.h>
#include <memory>

class TileComponent : public Component {
public:
  SDL_Rect gameMapTile;
  SDL_Rect tilemapTile;

  SDL_Texture *texture;

  std::string path;

  TileComponent() = default;

  ~TileComponent() { SDL_DestroyTexture(texture); }

  TileComponent(const std::string &sprite_sheet_path,
                const SDL_Rect &gameMapTile, const SDL_Rect &tilemapTile)
      : gameMapTile(std::move(gameMapTile)),
        tilemapTile(std::move(tilemapTile)),
        path(std::move(sprite_sheet_path)) {}

  void init() override { texture = TextureManager::LoadTexture(path); }

  void draw() override {
    TextureManager::Draw(texture, tilemapTile, gameMapTile, SDL_FLIP_NONE);
  }
};