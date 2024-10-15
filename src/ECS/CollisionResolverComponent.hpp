#pragma once

#include "Components.hpp"

class GravityComponent;

class CollisionResolver : public Component {
public:
  std::shared_ptr<TransformComponent> transform;
  std::shared_ptr<ColliderComponent> collider;
  std::shared_ptr<GravityComponent> gravity;

  void init() override;

  void update(uint_fast32_t step) override;
};
