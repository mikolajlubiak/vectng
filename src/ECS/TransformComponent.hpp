#pragma once

#include "Components.hpp"
#include "../Vector2D.hpp"
#include <cstdint>

struct TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;
	
	uint_fast16_t height = 92;
	uint_fast16_t width = 66;
	int_fast8_t scale = 1;

	uint_fast8_t speed = 3;

	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}
	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}
	TransformComponent(float x, float y, uint_fast16_t h, uint_fast16_t w, int_fast8_t sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
		
	}

	void init() override {
		velocity.x = 0.0f;
		velocity.y = 0.0f;
	}
	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};
