#include "TileComponent.hpp"

void TileComponent::update() {
  gameMapTile.x = static_cast<int>(position.x - Game::camera.x);
  gameMapTile.y = position.y;
}

void TileComponent::draw() {
  TextureManager::Draw(texture, tilemapTile, gameMapTile, SDL_FLIP_NONE);
}