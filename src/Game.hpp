#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstdint>

class Game {
public:
	Game();
	~Game();

	void init(const char *title, uint_fast32_t xpos, uint_fast32_t ypos, uint_fast16_t width, uint_fast16_t height, SDL_WindowFlags flags);

	void update();
	void render();
	void clean();
	bool running() { return isRunning; }

	static SDL_Renderer *renderer;
	static SDL_Event event;
private:
	SDL_Window *window;
	bool isRunning;
};
