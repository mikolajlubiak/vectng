#pragma once

#include "../Collision.hpp"
#include "../Game.hpp"
#include "Components.hpp"

class GravityComponent : public Component {
public:
  bool isInAir = false;

  float gravityVelocity = 0.02f;
  float jumpVelocity = -6.0f;

  std::shared_ptr<ColliderComponent> collider;
  std::shared_ptr<TransformComponent> transform;

  GravityComponent() = default;

  GravityComponent(float gravityVelocity, float jumpVelocity)
      : gravityVelocity(gravityVelocity), jumpVelocity(jumpVelocity) {}

  void init() override;

  void update(uint_fast32_t step) override;

  bool gravityCollision(std::shared_ptr<ColliderComponent> coll);
};
