#pragma once
#include "Game.hpp"

class Map {
public:
	Map();
	~Map();

	void LoadMap(uint8_t[32][32]);
	void DrawMap();

private:
	SDL_Rect src, dest;
	SDL_Texture *dirt;
	SDL_Texture *grass;
	SDL_Texture *water;
	uint8_t map[32][32];
};
