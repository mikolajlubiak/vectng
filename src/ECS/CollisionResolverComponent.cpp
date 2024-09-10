#include "CollisionResolverComponent.hpp"

void CollisionResolver::init() {
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

void CollisionResolver::update() {
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
              directionX * -6.0f;
        }

      } else {

        Vector2D normalizedVelocity =
            this->entity->getComponent<TransformComponent>().velocity;

        normalizedVelocity.Normalize();

        this->entity->getComponent<TransformComponent>().position +=
            normalizedVelocity * -6.0f;
      }
    }
  }
}
