#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Game {
public:
  Game();
  ~Game();

  void init(const char *title, unsigned int xpos, unsigned int ypos, uint16_t width, uint16_t height, SDL_WindowFlags flags);

  void handleEvents();
  void update();
  void render();
  void clean();
  bool running() { return isRunning; }

  static SDL_Renderer *renderer;

private:
  bool isRunning;
  SDL_Window *window;
};
