#include "SpriteComponent.hpp"

void SpriteComponent::init() {
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

void SpriteComponent::update() {
  if (animated) {
    transform->height = srcRect.h;
    transform->width = srcRect.w;
  }

  destRect.x = static_cast<int>(transform->position.x - Game::camera.x);
  destRect.y = static_cast<int>(transform->position.y);

  destRect.w = transform->width * transform->scale;
  destRect.h = transform->height * transform->scale;

  if (animated) {

    if (entity->getComponent<GravityComponent>().isInAir) {
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

void SpriteComponent::draw() {
  TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
}

void SpriteComponent::play(const std::string &animName) {
  const auto &animData = animations.at(animName);

  uint_fast64_t currentFrame = SDL_GetTicks64() / animData.frame_delay;

  uint_fast64_t index =
      static_cast<uint_fast64_t>(currentFrame % animData.sprites.size());

  srcRect = animData.sprites[index];
}
