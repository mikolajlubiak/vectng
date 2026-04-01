#pragma once

#include "../Collision.hpp"
#include "../Game.hpp"
#include "Components.hpp"

class GravityComponent : public Component {
public:
  bool isInAir = false;
  float gravityVelocity = 0.2f;
  float jumpVelocity = -6.0f;

  GravityComponent() = default;

  GravityComponent(float gravityVelocity, float jumpVelocity)
      : gravityVelocity(gravityVelocity), jumpVelocity(jumpVelocity) {}

  void init() override;
  void update(uint_fast32_t step) override;
  bool isLandingOn(const std::shared_ptr<ColliderComponent> &coll) const;

private:
  std::shared_ptr<ColliderComponent> collider;
  std::shared_ptr<TransformComponent> transform;
};
