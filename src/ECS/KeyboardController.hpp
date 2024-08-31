#pragma once

#include "../Game.hpp"
#include "Components.hpp"
#include "ECS.hpp"

class KeyboardController : public Component {
public:
  std::shared_ptr<TransformComponent> transform;

  void init() override {
    transform = entity->getComponentPtr<TransformComponent>();
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
  }

  void update() override {
    while (SDL_PollEvent(&Game::event)) {
      if (Game::event.type == SDL_KEYDOWN) {
        switch (Game::event.key.keysym.sym) {
        case SDLK_w:
          transform->velocity.y = -1;
          break;
        case SDLK_s:
          transform->velocity.y = 1;
          break;
        case SDLK_a:
          transform->velocity.x = -1;
          break;
        case SDLK_d:
          transform->velocity.x = 1;
          break;
        case SDLK_ESCAPE:
          Game::isRunning = false;
          break;
        default:
          break;
        }
      } else if (Game::event.type == SDL_KEYUP) {
        switch (Game::event.key.keysym.sym) {
        case SDLK_w:
        case SDLK_s:
          transform->velocity.y = 0.0f;
          break;
        case SDLK_a:
        case SDLK_d:
          transform->velocity.x = 0.0f;
          break;
        default:
          break;
        }
      } else if (Game::event.type == SDL_QUIT) {
        Game::isRunning = false;
      }
    }
  }
};
