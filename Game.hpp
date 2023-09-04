#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <iostream>

class Game {
public:
  Game();
  ~Game();

  void init(const char *title, int xpos, int ypos, Uint16 width, Uint16 height, SDL_WindowFlags flags);

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
