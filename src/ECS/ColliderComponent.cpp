#include "ColliderComponent.hpp"

void ColliderComponent::update() {
  if (this->entity->hasComponent<TransformComponent>()) {
    auto transform = this->entity->getComponentPtr<TransformComponent>();

    collider.x = transform->position.x;
    collider.y = transform->position.y;
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;

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