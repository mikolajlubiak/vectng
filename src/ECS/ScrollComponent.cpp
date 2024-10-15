#include "ScrollComponent.hpp"

void ScrollComponent::update(uint_fast32_t step) {
  if (this->entity->hasComponent<TransformComponent>()) {
    auto transform = this->entity->getComponentPtr<TransformComponent>();

    scrolledPos.x = (transform->position.x -
                     (2 * playerTransform->position.x - initialPlayerPos.x));

  } else if (this->entity->hasComponent<TileComponent>()) {
    auto tile = this->entity->getComponentPtr<TileComponent>();

    scrolledPos.x = (tile->gameMapTile.x -
                     (2 * playerTransform->position.x - initialPlayerPos.x));
  }
}