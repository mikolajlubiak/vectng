#include "Game.hpp"

int main() {
  constexpr uint_fast32_t TICKRATE = 1000 / 100; // 100 ticks per second

  constexpr uint_fast32_t WIDTH = 1280;
  constexpr uint_fast32_t HEIGHT = WIDTH / 16 * 9;

  uint_fast64_t lastTime = SDL_GetTicks64();
  uint_fast64_t nowTime = 0;
  uint_fast64_t deltaTime = 0;
  uint_fast64_t accumulator = 0;

  const std::unique_ptr<Game> game = std::make_unique<Game>();

  game->init("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH,
             HEIGHT, false);

  while (game->running()) {
    nowTime = SDL_GetTicks64();
    deltaTime = nowTime - lastTime;
    accumulator += deltaTime;
    lastTime = nowTime;

    while (accumulator > TICKRATE) {
      game->update(TICKRATE);
      accumulator -= TICKRATE;
    }

    game->render();
  }

  game->clean();

  return 0;
}
