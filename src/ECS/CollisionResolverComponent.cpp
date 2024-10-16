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
}

void CollisionResolver::update(const uint_fast32_t step) {
  for (std::shared_ptr<ColliderComponent> coll : Game::colliders) {
    if (Collision::AABB(collider, coll) && (collider->tag != coll->tag)) {

      if (this->entity->hasComponent<GravityComponent>()) {
        if (!this->entity->getComponent<GravityComponent>().gravityCollision(
                coll)) {
          horizontal_collision(coll);
        }
      } else {
        all_collisions(coll);
      }
    }
  }
}

inline void CollisionResolver::horizontal_collision(
    const std::shared_ptr<ColliderComponent> coll) {
  if ((transform->position.x + static_cast<float>(transform->width) / 2) -
          (static_cast<float>(coll->collider.x) +
           static_cast<float>(coll->collider.w) / 2) <
      0) {
    transform->position.x = static_cast<float>(coll->collider.x) -
                            static_cast<float>(transform->width);
  } else {
    transform->position.x = static_cast<float>(coll->collider.x) +
                            static_cast<float>(transform->width);
  }
}

inline void CollisionResolver::vertical_collision(
    const std::shared_ptr<ColliderComponent> coll) {
  if ((transform->position.y + static_cast<float>(transform->height) / 2) -
          (static_cast<float>(coll->collider.y) +
           static_cast<float>(coll->collider.h) / 2) <
      0) {
    transform->position.y = static_cast<float>(coll->collider.y) -
                            static_cast<float>(transform->height);
  } else {
    transform->position.y = static_cast<float>(coll->collider.y) +
                            static_cast<float>(transform->height);
  }
}

inline void CollisionResolver::all_collisions(
    const std::shared_ptr<ColliderComponent> coll) {
  horizontal_collision(coll);
  vertical_collision(coll);
}
