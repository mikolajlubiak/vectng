#pragma once

#include "../Vector2D.hpp"
#include "Components.hpp"
#include <cstdint>

class TransformComponent : public Component {
public:
  Vector2D position;
  Vector2D velocity;

  uint_fast32_t height = 0;
  uint_fast32_t width = 0;
  uint_fast32_t scale = 1;

  float speed = 0.1f;

  TransformComponent() = default;

  TransformComponent(float x, float y)
      : position(x, y) {}

  TransformComponent(float x, float y, uint_fast32_t h, uint_fast32_t w,
                     uint_fast32_t sc)
      : position(x, y), height(h), width(w), scale(sc) {}

  explicit TransformComponent(uint_fast32_t sc)
      : scale(sc) {}

  void init() override { velocity.Zero(); }

  void update(uint_fast32_t step) override {
    // Position update is handled by GravityComponent for physical entities.
    // Non-physical entities (tiles) don't need velocity application.
  }
};
