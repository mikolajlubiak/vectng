#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <stdint.h>
#include <vector>

class ColliderComponent;

class Game {
public:
  void init(const char *title, uint_fast32_t xpos, uint_fast32_t ypos,
            uint_fast32_t width, uint_fast32_t height, bool fullscreen);

  void update();
  void render();
  void clean();
  bool running() { return isRunning; }

  static SDL_Renderer *renderer;
  static SDL_Event event;
  static bool isRunning;
  static std::vector<std::shared_ptr<ColliderComponent>> colliders;

private:
  SDL_Window *window;
};
