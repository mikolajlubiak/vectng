#pragma once

#include "Components.hpp"
#include "../Vector2D.hpp"
#include <stdint.h>

struct TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;
	
	uint_fast32_t height = 92;
	uint_fast32_t width = 66;
	int_fast32_t scale = 1;

	uint_fast32_t speed = 3;

	TransformComponent() {
		position.Zero();
	}
	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}
	TransformComponent(float x, float y, uint_fast32_t h, uint_fast32_t w, int_fast32_t sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}
	TransformComponent(int_fast32_t sc) {
		position.Zero();
		scale = sc;
	}

	void init() override {
		velocity.Zero();
	}
	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};
