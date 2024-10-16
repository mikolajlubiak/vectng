#pragma once

#include "../Vector2D.hpp"
#include "Components.hpp"
#include <stdint.h>

class TransformComponent : public Component {
public:
  Vector2D position;
  Vector2D velocity;

  uint_fast32_t height = 0;
  uint_fast32_t width = 0;
  uint_fast32_t scale = 1;

  float speed = 0.1f;

  TransformComponent() { position.Zero(); }

  TransformComponent(float x, float y) {
    position.x = x;
    position.y = y;
  }

  TransformComponent(float x, float y, uint_fast32_t h, uint_fast32_t w,
                     uint_fast32_t sc) {
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

  void init() override { velocity.Zero(); }

  void update(const uint_fast32_t step) override {
    position += velocity * (step * speed);
  }
};
