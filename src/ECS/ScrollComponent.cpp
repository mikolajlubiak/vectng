#include "ScrollComponent.hpp"

void ScrollComponent::update(uint_fast32_t step) {
  float cameraOffset = playerTransform->position.x - initialPlayerPos.x;

  if (entity->hasComponent<TransformComponent>()) {
    auto transform = entity->getComponentPtr<TransformComponent>();
    scrolledPos.x = transform->position.x - cameraOffset;
  } else if (entity->hasComponent<TileComponent>()) {
    auto tile = entity->getComponentPtr<TileComponent>();
    scrolledPos.x = static_cast<float>(tile->gameMapTile.x) - cameraOffset;
  }
}
