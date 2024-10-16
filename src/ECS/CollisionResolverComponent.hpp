#pragma once

#include "Components.hpp"

class GravityComponent;

class CollisionResolver : public Component {
public:
  std::shared_ptr<TransformComponent> transform;
  std::shared_ptr<ColliderComponent> collider;

  void init() override;

  void update(const uint_fast32_t step) override;

  inline void
  horizontal_collision(const std::shared_ptr<ColliderComponent> coll);
  inline void vertical_collision(const std::shared_ptr<ColliderComponent> coll);
  inline void all_collisions(const std::shared_ptr<ColliderComponent> coll);
};
