#include "Game.hpp"

Game *game = nullptr;

int main() {
  const uint_fast32_t FPS = 60;
  const uint_fast32_t FRAME_DELAY = 1000 / FPS;

  uint_fast64_t frameStart;
  uint_fast64_t frameTime;

  game = new Game;

  game->init("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720,
             false);

  while (game->running()) {
    frameStart = SDL_GetTicks64();

    game->update();
    game->render();

    frameTime = SDL_GetTicks() - frameStart;

    if (FRAME_DELAY > frameTime) {
      SDL_Delay(FRAME_DELAY - frameTime);
    }
  }

  game->clean();

  return 0;
}
