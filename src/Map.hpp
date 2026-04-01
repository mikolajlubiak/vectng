#pragma once
#include <cstdint>
#include <string>

class Map {
public:
  static void LoadMap(const std::string &path, uint_fast32_t tilemapSizeX,
                      uint_fast32_t tilemapSizeY);
};
