#pragma once

#include "../Game.hpp"
#include "Components.hpp"
#include <SDL2/SDL.h>
#include <string>

class ColliderComponent : public Component {
public:
  SDL_Rect collider;
  std::string tag;

  explicit ColliderComponent(std::string t) : collider{0, 0, 0, 0}, tag(std::move(t)) {}

  void init() override {
    Game::colliders.push_back(entity->getComponentPtr<ColliderComponent>());
  }

  // Re-sync collider rect from the entity's transform or tile component.
  void sync();
  void update(uint_fast32_t step) override;
};
