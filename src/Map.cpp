#include "Map.hpp"
#include "Game.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

void Map::LoadMap(const std::string &path, uint_fast32_t tilemapSizeX,
                  uint_fast32_t tilemapSizeY) {
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "Failed to open tilemap: " << path << std::endl;
    return;
  }

  std::string line;
  uint_fast32_t row = 0;

  while (std::getline(file, line) && row < tilemapSizeY) {
    std::stringstream lineStream(line);
    std::string number;
    uint_fast32_t col = 0;

    while (std::getline(lineStream, number, ',') && col < tilemapSizeX) {
      try {
        int tileNumber = std::stoi(number);
        if (tileNumber > 0) {
          Game::AddTile(static_cast<uint_fast32_t>(tileNumber - 1), col, row);
        }
      } catch (const std::exception &e) {
        std::cerr << "Invalid tile at (" << col << "," << row
                  << "): " << e.what() << std::endl;
      }
      col++;
    }
    row++;
  }
}
