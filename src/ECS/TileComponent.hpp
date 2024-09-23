#pragma once

#include "../TextureManager.hpp"
#include "../Vector2D.hpp"
#include "Components.hpp"
#include <SDL2/SDL.h>
#include <memory>

class ScrollComponent;

class TileComponent : public Component {
public:
  SDL_Rect tilemapTile;
  SDL_Rect gameMapTile;

  SDL_Texture *texture;

  Vector2D position;

  ~TileComponent() { SDL_DestroyTexture(texture); }

  TileComponent(const std::string &sprite_sheet_path,
                const SDL_Rect &gameMapTile, const SDL_Rect &tilemapTile)
      : tilemapTile(std::move(tilemapTile)),
        gameMapTile(std::move(gameMapTile)),
        texture(TextureManager::LoadTexture(sprite_sheet_path)),
        position(static_cast<float>(gameMapTile.x),
                 static_cast<float>(gameMapTile.y)) {}

  void update() override;

  void draw() override;
};