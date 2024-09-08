#pragma once

#include "../Game.hpp"
#include "Components.hpp"
#include <SDL2/SDL.h>
#include <string>

class ColliderComponent : public Component {
public:
  SDL_Rect collider;
  std::string tag;

  std::shared_ptr<TransformComponent> transform;

  ColliderComponent(std::string t) { tag = t; }

  void init() override {
    if (!entity->hasComponent<TransformComponent>()) {
      entity->addComponent<TransformComponent>();
    }

    transform = entity->getComponentPtr<TransformComponent>();

    Game::colliders.push_back(entity->getComponentPtr<ColliderComponent>());
  }

  void update() override {
    collider.x = transform->position.x;
    collider.y = transform->position.y;
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;
  }
};
