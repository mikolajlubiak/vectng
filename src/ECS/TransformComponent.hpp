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
		position.x = 0.0;
		position.y = 0.0;
	}
	TransformComponent(uint_fast32_t x, uint_fast32_t y) {
		position.x = x;
		position.y = y;
	}
	TransformComponent(uint_fast32_t x, uint_fast32_t y, uint_fast16_t h, uint_fast16_t w, int_fast8_t sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
		
	}

	void init() override {
		velocity.x = 0;
		velocity.y = 0;
	}
	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};
