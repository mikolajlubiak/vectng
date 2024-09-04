#include "Animation.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

std::unordered_map<std::string, SDL_Rect>
parseSpriteSheetData(const std::string &path) {
  std::unordered_map<std::string, SDL_Rect> spriteSheetData;

  // Open the file
  std::ifstream inputFile(path);
  if (!inputFile.is_open()) {
    std::cerr << "Error: Could not open the file." << std::endl;
    return spriteSheetData;
  }

  std::string line;

  // Read the file line by line
  while (std::getline(inputFile, line)) {
    // Remove whitespace and split the line by '='
    uint_fast32_t equalPos = line.find('=');

    if (equalPos != std::string::npos) {
      std::string name = line.substr(0, equalPos);
      std::string values = line.substr(equalPos + 1);

      // Trim the name
      name.erase(0, name.find_first_not_of(" \t"));
      name.erase(name.find_last_not_of(" \t") + 1);

      // Parse the values
      std::istringstream valueStream(values);
      SDL_Rect spriteData;
      valueStream >> spriteData.x >> spriteData.y >> spriteData.w >>
          spriteData.h;

      // Store in the map
      spriteSheetData[name] = spriteData;
    }
  }

  // Close the file
  inputFile.close();

  return spriteSheetData;
}

std::vector<SDL_Rect> getSpritesVector(
    const std::string &searchTerm,
    const std::unordered_map<std::string, SDL_Rect> &spriteSheetData) {

  std::vector<std::string> filteredNames;

  for (const auto &[name, _] : spriteSheetData) {
    if (name.compare(0, searchTerm.length(), searchTerm) == 0) {
      filteredNames.emplace_back(name);
    }
  }

  std::sort(filteredNames.begin(), filteredNames.end());

  std::vector<SDL_Rect> rects;
  for (const auto &name : filteredNames) {
    rects.emplace_back(spriteSheetData.at(name));
  }

  return rects;
}
