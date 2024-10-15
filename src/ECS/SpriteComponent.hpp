#pragma once

#include "../TextureManager.hpp"
#include "Animation.hpp"
#include "Components.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <array>
#include <string>
#include <unordered_map>

class SpriteComponent : public Component {
private:
  std::shared_ptr<TransformComponent> transform;
  SDL_Texture *texture;
  SDL_Rect srcRect, destRect;

  bool usesSpritesheet = false;
  bool animated = false;
  std::unordered_map<std::string, SDL_Rect> spriteSheetData;
  std::unordered_map<std::string, Animation> animations;

public:
  SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

  SpriteComponent(const std::string &path) { setTex(path); }
  ~SpriteComponent() { SDL_DestroyTexture(texture); }

  SpriteComponent(const std::string &sprite_sheet_path,
                  const std::string &sprite_sheet_data_path,
                  const std::array<std::string, 3> &searchTerms) {
    usesSpritesheet = true;
    animated = true;

    spriteSheetData = parseSpriteSheetData(sprite_sheet_data_path);

    setTex(sprite_sheet_path);

    Animation idle(getSpritesVector(searchTerms[0], spriteSheetData), 1);
    Animation walk(getSpritesVector(searchTerms[1], spriteSheetData), 40);
    Animation jump(getSpritesVector(searchTerms[2], spriteSheetData), 1);

    animations.emplace("idle", idle);
    animations.emplace("walk", walk);
    animations.emplace("jump", jump);

    play("idle");
  }

  void setTex(const std::string &path) {
    texture = TextureManager::LoadTexture(path);
  }

  void init() override;

  void update(uint_fast32_t step) override;

  void draw() override;

  void play(const std::string &animName);
};