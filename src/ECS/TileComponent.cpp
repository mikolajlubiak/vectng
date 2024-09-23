#include "TileComponent.hpp"

void TileComponent::update() {
  gameMapTile.x = position.x - Game::camera.x;
  gameMapTile.y = position.y - Game::camera.y;
}

void TileComponent::draw() {
  TextureManager::Draw(texture, tilemapTile, gameMapTile, SDL_FLIP_NONE);
}