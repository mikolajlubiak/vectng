#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <vector>

struct Animation {
  const std::vector<SDL_Rect> sprites;
  uint_fast64_t frame_delay;

  Animation(const std::vector<SDL_Rect> sprites, uint_fast64_t frame_delay)
      : sprites(std::move(sprites)), frame_delay(frame_delay) {}
};

std::unordered_map<std::string, SDL_Rect>
parseSpriteSheetData(const std::string &path);

std::vector<SDL_Rect> getSpritesVector(
    const std::string &searchTerm,
    const std::unordered_map<std::string, SDL_Rect> &spriteSheetData);