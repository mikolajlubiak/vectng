#pragma once

#include "../TextureManager.hpp"
#include "ECS.hpp"
#include <SDL2/SDL.h>

class SpriteComponent : public Component {
private:
  PositionComponent *position;
  SDL_Texture *texture;
  SDL_Rect srcRect, destRect;

public:
  SpriteComponent() = default;
  SpriteComponent(const char *path) { setTex(path); }

  void setTex(const char *path) { texture = TextureManager::LoadTexture(path); }

  void init() override {
    position = &entity->getComponent<PositionComponent>();

    srcRect.x = srcRect.y = 0;
    srcRect.w = destRect.w = 66;
    srcRect.h = destRect.h = 92;
  }
  void update() override {
    destRect.x = position->x();
    destRect.y = position->y();
  }
  void draw() override { TextureManager::Draw(texture, srcRect, destRect); }
};
