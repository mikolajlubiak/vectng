#pragma once
#include "Game.hpp"

class GameObject {
public:
	GameObject(const char *textureSheet, uint_fast8_t x, uint_fast8_t y);
	~GameObject();
	void Update();
	void Render();

private:
	uint_fast8_t xpos;
	uint_fast8_t ypos;

	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
};
