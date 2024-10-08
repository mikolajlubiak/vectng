#include "GravityComponent.hpp"

void GravityComponent::init() {
  if (!entity->hasComponent<ColliderComponent>()) {
    entity->addComponent<ColliderComponent>("gravity");
  }

  transform = entity->getComponentPtr<TransformComponent>();
  collider = entity->getComponentPtr<ColliderComponent>();
}

void GravityComponent::update() {
  transform->velocity.y += this->gravityVelocity;

  for (std::shared_ptr<ColliderComponent> coll : Game::colliders) {
    if (Collision::AABB(*collider, *coll) && (collider->tag != coll->tag)) {

      if (gravityCollision(coll)) {

        transform->position.y = coll->collider.y - transform->height;

        this->isInAir = false;

        transform->velocity.y = std::min(0.0f, transform->velocity.y);
      }
    }
  }
}

bool GravityComponent::gravityCollision(
    std::shared_ptr<ColliderComponent> coll) {
  return coll->tag == "floor_tile" &&
         transform->position.y <= coll->collider.y - coll->collider.h;
}