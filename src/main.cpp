#include "Game.hpp"
#include <cstdint>
#include <memory>

int main() {
  constexpr uint_fast32_t kTickrate = 1000 / 100;

  constexpr uint_fast32_t kWidth = 1280;
  constexpr uint_fast32_t kHeight = kWidth / 16 * 9;

  uint_fast64_t lastTime = SDL_GetTicks64();
  uint_fast64_t accumulator = 0;

  auto game = std::make_unique<Game>();

  game->init("VectNG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kWidth,
             kHeight, false);

  while (game->running()) {
    uint_fast64_t nowTime = SDL_GetTicks64();
    uint_fast64_t deltaTime = nowTime - lastTime;
    accumulator += deltaTime;
    lastTime = nowTime;

    while (accumulator > kTickrate) {
      game->update(kTickrate);
      accumulator -= kTickrate;
    }

    game->render();
  }

  game->clean();
  return 0;
}
