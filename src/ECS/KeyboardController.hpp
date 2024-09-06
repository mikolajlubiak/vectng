#pragma once

#include "../Game.hpp"
#include "Components.hpp"
#include "ECS.hpp"

class KeyboardController : public Component {
public:
  std::shared_ptr<TransformComponent> transform;
  std::shared_ptr<SpriteComponent> sprite;

  void init() override {
    transform = entity->getComponentPtr<TransformComponent>();
    sprite = entity->getComponentPtr<SpriteComponent>();

    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
  }

  void update() override {
    while (SDL_PollEvent(&Game::event)) {
      switch (Game::event.type) {

      case SDL_KEYDOWN:
        switch (Game::event.key.keysym.sym) {
        case SDLK_SPACE:
          if (!transform->isInAir && transform->velocity.y >= 0.0f) {
            transform->velocity.y += -6.0f;
            transform->isInAir = true;
          }
          break;
        case SDLK_a:
          transform->velocity.x = -1.0f;
          break;
        case SDLK_d:
          transform->velocity.x = 1.0f;
          break;
        case SDLK_ESCAPE:
          Game::isRunning = false;
          break;
        default:
          break;
        }

        break;

      case SDL_KEYUP:
        switch (Game::event.key.keysym.sym) {
        case SDLK_a:
        case SDLK_d:
          transform->velocity.x = 0.0f;
          break;
        default:
          break;
        }

        break;

      case SDL_QUIT:
        Game::isRunning = false;
        break;

      default:
        break;
      }
    }
  }
};
