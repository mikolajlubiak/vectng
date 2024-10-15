#pragma once

#include "../Vector2D.hpp"
#include "Components.hpp"

class ScrollComponent : public Component {
public:
  std::shared_ptr<TransformComponent> playerTransform;
  Vector2D initialPlayerPos;

  Vector2D scrolledPos;

  ScrollComponent(std::shared_ptr<TransformComponent> playerTransform,
                  Vector2D initialPlayerPos)
      : playerTransform(playerTransform), initialPlayerPos(initialPlayerPos) {}

  void update(uint_fast32_t step) override;
};
