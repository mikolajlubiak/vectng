#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <vector>

struct Animation {
  std::vector<std::string> sprites;
  uint_fast32_t frame_delay;

  Animation() = default;

  Animation(std::vector<std::string> sprites, uint_fast32_t frame_delay) {
    this->sprites = sprites;
    this->frame_delay = frame_delay;
  };
};

std::unordered_map<std::string, SDL_Rect>
parseSpriteSheetData(const std::string &path);

std::vector<std::string> getSpritesVector(
    const std::string &searchTerm,
    const std::unordered_map<std::string, SDL_Rect> &spriteSheetData);