#pragma once

#include "../TextureManager.hpp"
#include <SDL2/SDL.h>
#include "Components.hpp"


class SpriteComponent : public Component {
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char *path) { setTex(path); }

	void setTex(const char *path) { texture = TextureManager::LoadTexture(path); }

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = destRect.w = 66;
		srcRect.h = destRect.h = 92;
	}
	void update() override {
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}
	void draw() override { TextureManager::Draw(texture, srcRect, destRect); }
};
