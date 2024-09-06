#pragma once
#include <stdint.h>
#include <string>

class Map {
public:
  Map() = default;
  ~Map() = default;

  static void LoadMap(const std::string &path, const uint_fast32_t tilemapSizeX,
                      const uint_fast32_t tilemapSizeY);

private:
};
