#include "ColliderComponent.hpp"

void ColliderComponent::sync() {
  if (entity->hasComponent<TransformComponent>()) {
    auto transform = entity->getComponentPtr<TransformComponent>();

    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w =
        static_cast<int>(transform->width) * static_cast<int>(transform->scale);
    collider.h = static_cast<int>(transform->height) *
                 static_cast<int>(transform->scale);
  } else if (entity->hasComponent<TileComponent>()) {
    auto tile = entity->getComponentPtr<TileComponent>();
    collider = tile->gameMapTile;
  }
}

void ColliderComponent::update(uint_fast32_t step) { sync(); }
