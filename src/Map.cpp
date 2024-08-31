#include "Map.hpp"
#include "Game.hpp"
#include <SDL2/SDL_render.h>
#include <fstream>

void Map::LoadMap(const std::string path, uint_fast32_t size_x,
                  uint_fast32_t size_y) {
  char tile;
  std::ifstream mapFile;

  mapFile.open(path);

  for (uint_fast32_t y = 0; y < size_y; y++) {
    for (uint_fast32_t x = 0; x < size_x; x++) {
      mapFile.get(tile);
      Game::AddTile(static_cast<tileType>(atoi(&tile)), x * 70, y * 70);
      mapFile.ignore();
    }
  }

  mapFile.close();
}