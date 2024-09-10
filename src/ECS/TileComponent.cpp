#include "TileComponent.hpp"

void TileComponent::draw() {
  if (this->entity->hasComponent<ScrollComponent>()) {
    auto scroll = this->entity->getComponentPtr<ScrollComponent>();

    SDL_Rect scrolledRect = gameMapTile;

    scrolledRect.x = scroll->scrolledPos.x;

    TextureManager::Draw(texture, tilemapTile, scrolledRect, SDL_FLIP_NONE);
  } else {
    TextureManager::Draw(texture, tilemapTile, gameMapTile, SDL_FLIP_NONE);
  }
}