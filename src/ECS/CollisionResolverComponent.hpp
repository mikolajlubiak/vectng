#pragma once

#include "Components.hpp"

class CollisionResolver : public Component {
public:
  std::shared_ptr<TransformComponent> transform;
  std::shared_ptr<ColliderComponent> collider;
  std::shared_ptr<GravityComponent> gravity;

  CollisionResolver() = default;

  void init() override {
    if (!entity->hasComponent<TransformComponent>()) {
      entity->addComponent<TransformComponent>();
    }

    if (!entity->hasComponent<ColliderComponent>()) {
      entity->addComponent<ColliderComponent>("collision_resolver");
    }

    transform = entity->getComponentPtr<TransformComponent>();
    collider = entity->getComponentPtr<ColliderComponent>();
    gravity = entity->getComponentPtr<GravityComponent>();
  }

  void update() override {
    for (std::shared_ptr<ColliderComponent> coll : Game ::colliders) {
      if (Collision::AABB(this->entity->getComponent<ColliderComponent>(),
                          *coll) &&
          (this->entity->getComponent<ColliderComponent>().tag != coll->tag)) {

        if (this->entity->hasComponent<GravityComponent>()) {
          if (!this->entity->getComponent<GravityComponent>().gravityCollision(
                  coll)) {

            float directionX = 0.0f;

            if (this->entity->getComponent<TransformComponent>().velocity.x !=
                0.0f) {
              directionX =
                  this->entity->getComponent<TransformComponent>().velocity.x /
                  std::abs(this->entity->getComponent<TransformComponent>()
                               .velocity.x);
            }

            this->entity->getComponent<TransformComponent>().position.x +=
                directionX * -3.0f;
          }

        } else {

          Vector2D normalizedVelocity =
              this->entity->getComponent<TransformComponent>().velocity;

          normalizedVelocity.Normalize();

          this->entity->getComponent<TransformComponent>().position +=
              normalizedVelocity * -3.0f;
        }
      }
    }
  }
};
