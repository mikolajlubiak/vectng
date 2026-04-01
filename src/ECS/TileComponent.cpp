#include "TileComponent.hpp"

void TileComponent::draw() {
  if (entity->hasComponent<ScrollComponent>()) {
    auto scroll = entity->getComponentPtr<ScrollComponent>();
    SDL_Rect scrolledRect = gameMapTile;
    scrolledRect.x = static_cast<int>(scroll->scrolledPos.x);
    TextureManager::Draw(texture, tilemapTile, scrolledRect, SDL_FLIP_NONE);
  } else {
    TextureManager::Draw(texture, tilemapTile, gameMapTile, SDL_FLIP_NONE);
  }
}