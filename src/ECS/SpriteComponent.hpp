#pragma once

#include "../TextureManager.hpp"
#include "Animation.hpp"
#include "Components.hpp"
#include <SDL2/SDL.h>
#include <array>
#include <string>
#include <unordered_map>

class SpriteComponent : public Component {
public:
  SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

  explicit SpriteComponent(const std::string &path) { setTex(path); }

  SpriteComponent(const std::string &sprite_sheet_path,
                  const std::string &sprite_sheet_data_path,
                  const std::array<std::string, 3> &searchTerms);

  void setTex(const std::string &path) {
    texture = TextureManager::LoadTexture(path);
  }

  void init() override;
  void update(uint_fast32_t step) override;
  void draw() override;
  void play(const std::string &animName);

private:
  std::shared_ptr<TransformComponent> transform;
  // Owned by TextureManager cache, not freed here
  SDL_Texture *texture = nullptr;
  SDL_Rect srcRect{};
  SDL_Rect destRect{};

  bool usesSpritesheet = false;
  bool animated = false;
  std::unordered_map<std::string, SDL_Rect> spriteSheetData;
  std::unordered_map<std::string, Animation> animations;
};
