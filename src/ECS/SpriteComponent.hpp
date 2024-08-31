#pragma once

#include "../TextureManager.hpp"
#include "Components.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string>

class SpriteComponent : public Component {
private:
  std::shared_ptr<TransformComponent> transform;
  SDL_Texture *texture;
  SDL_Rect srcRect, destRect;

public:
  SpriteComponent() = default;
  SpriteComponent(const std::string path) { setTex(path); }
  ~SpriteComponent() { SDL_DestroyTexture(texture); }

  void setTex(const std::string path) {
    texture = TextureManager::LoadTexture(path);
  }

  void init() override {
    transform = entity->getComponentPtr<TransformComponent>();

    srcRect.x = srcRect.y = 0;
    srcRect.w = transform->width;
    srcRect.h = transform->height;
  }
  void update() override {
    destRect.x = static_cast<int>(transform->position.x);
    destRect.y = static_cast<int>(transform->position.y);

    destRect.w = transform->width * transform->scale;
    destRect.h = transform->height * transform->scale;
  }
  void draw() override { TextureManager::Draw(texture, srcRect, destRect); }
};
