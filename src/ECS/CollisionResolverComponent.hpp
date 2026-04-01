#pragma once

#include "Components.hpp"

class GravityComponent;

class CollisionResolver : public Component {
public:
  void init() override;
  void update(uint_fast32_t step) override;

private:
  std::shared_ptr<TransformComponent> transform;
  std::shared_ptr<ColliderComponent> collider;

  void horizontal_collision(const std::shared_ptr<ColliderComponent> &coll);
  void vertical_collision(const std::shared_ptr<ColliderComponent> &coll);
  void all_collisions(const std::shared_ptr<ColliderComponent> &coll);
};
