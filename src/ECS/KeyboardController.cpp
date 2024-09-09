#include "KeyboardController.hpp"

class GravityComponent;

void KeyboardController::init() {
  transform = entity->getComponentPtr<TransformComponent>();
  gravity = entity->getComponentPtr<GravityComponent>();

  SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
}

void KeyboardController::update() {
  while (SDL_PollEvent(&Game::event)) {
    switch (Game::event.type) {

    case SDL_KEYDOWN:
      switch (Game::event.key.keysym.sym) {
      case SDLK_SPACE:
        if (!gravity->isInAir && transform->velocity.y >= 0.0f) {
          transform->velocity.y += gravity->jumpVelocity;
          gravity->isInAir = true;
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
