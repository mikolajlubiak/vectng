#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <stdint.h>
#include <vector>

constexpr uint_fast32_t SPRITE_HEIGHT = 92;
constexpr uint_fast32_t SPRITE_WIDTH = 66;

class ColliderComponent;

class Game {
public:
  void init(const char *title, int xpos, int ypos, int width, int height,
            bool fullscreen);

  void update(uint_fast32_t deltaTime);
  void render();
  void clean();
  bool running() { return isRunning; }

  static void AddTile(const uint_fast32_t tileNumber, const uint_fast32_t mapX,
                      const uint_fast32_t mapY);

  static SDL_Renderer *renderer;
  static SDL_Event event;
  static bool isRunning;
  static std::vector<std::shared_ptr<ColliderComponent>> colliders;

private:
  SDL_Window *window;
};
