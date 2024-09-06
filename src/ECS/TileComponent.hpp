#pragma once

#include "ECS.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"
#include <SDL2/SDL.h>
#include <memory>

class TileComponent : public Component {
public:
  std::shared_ptr<TransformComponent> transform;
  std::shared_ptr<SpriteComponent> sprite;

  SDL_Rect gameMapTile;
  SDL_Rect tilemapTile;

  std::string path;

  TileComponent() = default;

  TileComponent(const std::string &sprite_sheet_path,
                const SDL_Rect &gameMapTile, const SDL_Rect &tilemapTile)
      : gameMapTile(std::move(gameMapTile)),
        tilemapTile(std::move(tilemapTile)),
        path(std::move(sprite_sheet_path)) {}

  void init() override {
    entity->addComponent<TransformComponent>(static_cast<float>(gameMapTile.x),
                                             static_cast<float>(gameMapTile.y),
                                             gameMapTile.h, gameMapTile.w, 1);
    transform = entity->getComponentPtr<TransformComponent>();

    entity->addComponent<SpriteComponent>(path, tilemapTile);
    sprite = entity->getComponentPtr<SpriteComponent>();
  }
};