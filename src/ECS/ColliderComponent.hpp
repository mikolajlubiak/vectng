#pragma once

#include "../Game.hpp"
#include "Components.hpp"
#include <SDL2/SDL.h>
#include <string>

class ColliderComponent : public Component {
public:
  SDL_Rect collider;
  std::string tag;

  ColliderComponent(std::string t) : collider({0, 0, 0, 0}) { tag = t; }

  void init() override {
    Game::colliders.push_back(entity->getComponentPtr<ColliderComponent>());
  }

  void update(const uint_fast32_t step) override;
};
