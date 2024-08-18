#pragma once
#include "Game.hpp"

class Map {
public:
	Map();
	~Map();

	void LoadMap(const uint8_t[32][32]);
	void DrawMap();

private:
	SDL_Rect src, dest;
	SDL_Texture *dirt;
	SDL_Texture *grass;
	SDL_Texture *water;
	uint_fast8_t map[32][32];
};
