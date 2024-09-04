#pragma once
#include <stdint.h>
#include <string>

class Map {
public:
  Map() = default;
  ~Map() = default;

  static void LoadMap(const std::string &path, uint_fast32_t size_x,
                      uint_fast32_t size_y);

private:
};
