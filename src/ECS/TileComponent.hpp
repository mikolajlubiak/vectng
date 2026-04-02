#pragma once

#include "../TextureManager.hpp"
#include "../Vector2D.hpp"
#include "Components.hpp"
#include <SDL2/SDL.h>
#include <string>

class ScrollComponent;

class TileComponent : public Component {
public:
  SDL_Rect tilemapTile;
  SDL_Rect gameMapTile;
  std::string path;

  TileComponent(const std::string &sprite_sheet_path,
                const SDL_Rect &gameMapTile, const SDL_Rect &tilemapTile)
      : tilemapTile(tilemapTile), gameMapTile(gameMapTile),
        path(sprite_sheet_path) {}

  void init() override { texture = TextureManager::LoadTexture(path); }

  void draw() override;

private:
  // Texture is owned by TextureManager cache - do not destroy here
  SDL_Texture *texture = nullptr;
};
