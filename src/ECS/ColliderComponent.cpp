#include "ColliderComponent.hpp"

void ColliderComponent::update(const uint_fast32_t step) {
  if (this->entity->hasComponent<TransformComponent>()) {
    auto transform = this->entity->getComponentPtr<TransformComponent>();

    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w =
        static_cast<int>(transform->width) * static_cast<int>(transform->scale);
    collider.h = static_cast<int>(transform->height) *
                 static_cast<int>(transform->scale);

    if (this->entity->hasComponent<ScrollComponent>()) {
      auto scroll = this->entity->getComponentPtr<ScrollComponent>();

      collider.x = scroll->scrolledPos.x;
    }

  } else if (this->entity->hasComponent<TileComponent>()) {
    auto tile = this->entity->getComponentPtr<TileComponent>();
    collider = tile->gameMapTile;

    if (this->entity->hasComponent<ScrollComponent>()) {
      auto scroll = this->entity->getComponentPtr<ScrollComponent>();

      collider.x = scroll->scrolledPos.x;
    }
  }
}