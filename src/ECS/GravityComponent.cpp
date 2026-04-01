#include "GravityComponent.hpp"

void GravityComponent::init() {
  if (!entity->hasComponent<ColliderComponent>()) {
    entity->addComponent<ColliderComponent>("gravity");
  }

  transform = entity->getComponentPtr<TransformComponent>();
  collider = entity->getComponentPtr<ColliderComponent>();
}

void GravityComponent::update(uint_fast32_t step) {
  transform->velocity.y += gravityVelocity;

  for (const auto &coll : Game::colliders) {
    if (Collision::AABB(*collider, *coll) && (collider->tag != coll->tag)) {
      if (isLandingOn(coll)) {
        transform->position.y = static_cast<float>(coll->collider.y) -
                                static_cast<float>(transform->height);
        isInAir = false;
        transform->velocity.y = std::min(0.0f, transform->velocity.y);
      }
    }
  }
}

bool GravityComponent::isLandingOn(
    const std::shared_ptr<ColliderComponent> &coll) const {
  float entityCenterY =
      transform->position.y + static_cast<float>(transform->height) / 2.0f;
  float collCenterY =
      static_cast<float>(coll->collider.y) +
      static_cast<float>(coll->collider.h) / 2.0f;

  return coll->tag == "floor_tile" && entityCenterY < collCenterY;
}
