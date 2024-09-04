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

  bool animated = false;
  std::unordered_map<std::string, SDL_Rect> spriteSheetData;
  std::unordered_map<std::string, Animation> animations;

public:
  SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

  SpriteComponent() = default;
  SpriteComponent(const std::string &path) { setTex(path); }
  ~SpriteComponent() { SDL_DestroyTexture(texture); }

  SpriteComponent(const std::string &sprite_sheet_path,
                  const std::string &sprite_sheet_data_path,
                  const std::array<std::string, 2> &searchTerms) {
    animated = true;

    spriteSheetData = parseSpriteSheetData(sprite_sheet_data_path);

    setTex(sprite_sheet_path);

    Animation idle(getSpritesVector(searchTerms[0], spriteSheetData), 1);
    Animation walk(getSpritesVector(searchTerms[1], spriteSheetData), 80);

    animations["idle"] = idle;
    animations["walk"] = walk;

    play("idle");
  }

  void setTex(const std::string &path) {
    texture = TextureManager::LoadTexture(path);
  }

  void init() override {
    transform = entity->getComponentPtr<TransformComponent>();

    if (!animated) {
      srcRect.x = srcRect.y = 0;
      srcRect.w = transform->width;
      srcRect.h = transform->height;
    }
  }

  void update() override {
    if (animated) {
      transform->height = srcRect.h;
      transform->width = srcRect.w;
    }

    destRect.x = static_cast<int>(transform->position.x);
    destRect.y = static_cast<int>(transform->position.y);

    destRect.w = transform->width * transform->scale;
    destRect.h = transform->height * transform->scale;
  }

  void draw() override {
    TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
  }

  void play(const std::string &animName) {
    srcRect =
        spriteSheetData[animations[animName]
                            .sprites[static_cast<uint_fast32_t>(
                                         SDL_GetTicks64() /
                                         animations[animName].frame_delay) %
                                     animations[animName].sprites.size()]];
  }
};