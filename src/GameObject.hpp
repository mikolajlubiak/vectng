#pragma once
#include "Game.hpp"

class GameObject {
public:
	GameObject(const char *textureSheet, float x, float y);
	~GameObject();
	void Update();
	void Render();

private:
	uint16_t xpos;
	uint16_t ypos;

	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
};
