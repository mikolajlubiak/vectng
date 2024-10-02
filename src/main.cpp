#include "Game.hpp"

int main() {
  constexpr uint_fast32_t FPS = 60;
  constexpr uint_fast32_t FRAME_DELAY = 1000 / FPS;

  constexpr uint_fast32_t WIDTH = 1280;
  constexpr uint_fast32_t HEIGHT = WIDTH / 16 * 9;

  uint_fast64_t frameStart = 0;
  uint_fast64_t frameTime = 0;

  const std::unique_ptr<Game> game = std::make_unique<Game>();

  game->init("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH,
             HEIGHT, false);

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
