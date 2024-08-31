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

  SDL_Rect tileRect;
  uint_fast32_t tileID;
  std::string path;

  TileComponent() = default;

  TileComponent(uint_fast32_t x, uint_fast32_t y, uint_fast32_t w,
                uint_fast32_t h, uint_fast32_t id) {
    tileRect.x = x;
    tileRect.y = y;
    tileRect.w = w;
    tileRect.h = h;
    tileID = id;

    switch (tileID) {
    case 0:
      path = "assets/Tiles/grass.png";
      break;
    case 1:
      path = "assets/Tiles/liquidWater.png";
      break;
    case 2:
      path = "assets/Tiles/dirt.png";
      break;
    default:
      break;
    }
  }

  void init() override {
    entity->addComponent<TransformComponent>(static_cast<float>(tileRect.x),
                                             static_cast<float>(tileRect.y),
                                             tileRect.w, tileRect.h, 1);
    transform = entity->getComponentPtr<TransformComponent>();

    entity->addComponent<SpriteComponent>(path);
    sprite = entity->getComponentPtr<SpriteComponent>();
  }
};