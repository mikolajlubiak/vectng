#include "Map.hpp"
#include "Game.hpp"
#include <SDL2/SDL_render.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void Map::LoadMap(const std::string &path, const uint_fast32_t tilemapSizeX,
                  const uint_fast32_t tilemapSizeY) {
  // Open the file
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open the file." << std::endl;
    return;
  }

  std::string line;
  uint_fast32_t row = 0;

  // Read each line of the tilemap
  while (std::getline(file, line) && row < tilemapSizeY) {
    std::stringstream lineStream(line);
    std::string number;
    uint_fast32_t col = 0;

    // Read each number in the line
    while (std::getline(lineStream, number, ',') && col < tilemapSizeX) {
      Game::AddTile(std::stoi(number) - 1, col, row);
      col++;
    }
    row++;
  }

  // Close the file
  file.close();
}