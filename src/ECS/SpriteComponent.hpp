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

  SpriteComponent() = default;
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
    Animation walk(getSpritesVector(searchTerms[1], spriteSheetData), 80);
    Animation jump(getSpritesVector(searchTerms[2], spriteSheetData), 1);

    animations.emplace("idle", idle);
    animations.emplace("walk", walk);
    animations.emplace("jump", jump);

    play("idle");
  }

  SpriteComponent(const std::string &sprite_sheet_path,
                  const SDL_Rect &tileRect)
      : srcRect(std::move(tileRect)) {
    usesSpritesheet = true;

    setTex(sprite_sheet_path);
  }

  void setTex(const std::string &path) {
    texture = TextureManager::LoadTexture(path);
  }

  void init() override {
    if (!entity->hasComponent<TransformComponent>()) {
      entity->addComponent<TransformComponent>();
    }

    transform = entity->getComponentPtr<TransformComponent>();

    if (!usesSpritesheet) {
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

    if (animated) {

      if (entity->getComponent<TransformComponent>().velocity.y < 0.0f &&
          entity->hasComponent<GravityComponent>()) {
        play("jump");
      }

      else if (entity->getComponent<TransformComponent>().velocity.x != 0.0f) {
        play("walk");

        if (entity->getComponent<TransformComponent>().velocity.x < 0.0f) {
          spriteFlip = SDL_FLIP_HORIZONTAL;
        } else {
          spriteFlip = SDL_FLIP_NONE;
        }

      } else {
        play("idle");
      }
    }
  }

  void draw() override {
    TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
  }

  void play(const std::string &animName) {
    const auto &animData = animations.at(animName);

    uint_fast64_t currentFrame = SDL_GetTicks64() / animData.frame_delay;

    uint_fast64_t index =
        static_cast<uint_fast64_t>(currentFrame % animData.sprites.size());

    srcRect = animData.sprites[index];
  }
};