#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(
    const std::string &sprite_sheet_path,
    const std::string &sprite_sheet_data_path,
    const std::array<std::string, 3> &searchTerms) {
  usesSpritesheet = true;
  animated = true;

  spriteSheetData = parseSpriteSheetData(sprite_sheet_data_path);
  setTex(sprite_sheet_path);

  animations.emplace("idle",
                     Animation(getSpritesVector(searchTerms[0], spriteSheetData), 100));
  animations.emplace("walk",
                     Animation(getSpritesVector(searchTerms[1], spriteSheetData), 40));
  animations.emplace("jump",
                     Animation(getSpritesVector(searchTerms[2], spriteSheetData), 100));

  play("idle");
}

void SpriteComponent::init() {
  if (!entity->hasComponent<TransformComponent>()) {
    entity->addComponent<TransformComponent>();
  }

  transform = entity->getComponentPtr<TransformComponent>();

  if (!usesSpritesheet) {
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = static_cast<int>(transform->width);
    srcRect.h = static_cast<int>(transform->height);
  }
}

void SpriteComponent::update(uint_fast32_t step) {
  if (animated) {
    transform->height = srcRect.h;
    transform->width = srcRect.w;
  }

  destRect.x = static_cast<int>(transform->position.x);
  destRect.y = static_cast<int>(transform->position.y);

  destRect.w =
      static_cast<int>(transform->width) * static_cast<int>(transform->scale);
  destRect.h =
      static_cast<int>(transform->height) * static_cast<int>(transform->scale);

  if (animated) {
    if (entity->hasComponent<GravityComponent>() &&
        entity->getComponent<GravityComponent>().isInAir) {
      play("jump");
    } else if (transform->velocity.x != 0.0f) {
      play("walk");
      spriteFlip = (transform->velocity.x < 0.0f) ? SDL_FLIP_HORIZONTAL
                                                   : SDL_FLIP_NONE;
    } else {
      play("idle");
    }
  }
}

void SpriteComponent::draw() {
  if (entity->hasComponent<ScrollComponent>()) {
    auto scroll = entity->getComponentPtr<ScrollComponent>();
    SDL_Rect scrolledRect = destRect;
    scrolledRect.x = static_cast<int>(scroll->scrolledPos.x);
    TextureManager::Draw(texture, srcRect, scrolledRect, spriteFlip);
  } else {
    TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
  }
}

void SpriteComponent::play(const std::string &animName) {
  auto it = animations.find(animName);
  if (it == animations.end()) {
    return;
  }

  const auto &animData = it->second;
  uint_fast64_t currentFrame = SDL_GetTicks64() / animData.frame_delay;
  std::size_t index = currentFrame % animData.sprites.size();
  srcRect = animData.sprites[index];
}
