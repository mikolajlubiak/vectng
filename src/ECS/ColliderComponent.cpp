#include "ColliderComponent.hpp"

void ColliderComponent::update() {
  if (this->entity->hasComponent<TransformComponent>()) {
    auto transform = this->entity->getComponentPtr<TransformComponent>();

    collider.x = transform->position.x - Game::camera.x;
    collider.y = transform->position.y - Game::camera.y;
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;

  } else if (this->entity->hasComponent<TileComponent>()) {
    auto tile = this->entity->getComponentPtr<TileComponent>();

    collider = tile->gameMapTile;
    collider.x -= Game::camera.x;
    collider.y -= Game::camera.y;
  }
}