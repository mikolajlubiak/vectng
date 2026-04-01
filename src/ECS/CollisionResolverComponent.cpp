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

void CollisionResolver::update(uint_fast32_t step) {
  for (const auto &coll : Game::colliders) {
    if (Collision::AABB(collider, coll) && (collider->tag != coll->tag)) {
      if (entity->hasComponent<GravityComponent>()) {
        if (!entity->getComponent<GravityComponent>().isLandingOn(coll)) {
          horizontal_collision(coll);
        }
      } else {
        all_collisions(coll);
      }
    }
  }
}

void CollisionResolver::horizontal_collision(
    const std::shared_ptr<ColliderComponent> &coll) {
  float entityCenterX =
      transform->position.x + static_cast<float>(transform->width) / 2.0f;
  float collCenterX =
      static_cast<float>(coll->collider.x) +
      static_cast<float>(coll->collider.w) / 2.0f;

  if (entityCenterX < collCenterX) {
    transform->position.x = static_cast<float>(coll->collider.x) -
                            static_cast<float>(transform->width);
  } else {
    transform->position.x = static_cast<float>(coll->collider.x) +
                            static_cast<float>(coll->collider.w);
  }
}

void CollisionResolver::vertical_collision(
    const std::shared_ptr<ColliderComponent> &coll) {
  float entityCenterY =
      transform->position.y + static_cast<float>(transform->height) / 2.0f;
  float collCenterY =
      static_cast<float>(coll->collider.y) +
      static_cast<float>(coll->collider.h) / 2.0f;

  if (entityCenterY < collCenterY) {
    transform->position.y = static_cast<float>(coll->collider.y) -
                            static_cast<float>(transform->height);
  } else {
    transform->position.y = static_cast<float>(coll->collider.y) +
                            static_cast<float>(coll->collider.h);
  }
}

void CollisionResolver::all_collisions(
    const std::shared_ptr<ColliderComponent> &coll) {
  horizontal_collision(coll);
  vertical_collision(coll);
}
