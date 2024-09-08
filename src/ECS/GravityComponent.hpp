#pragma once

#include "../Collision.hpp"
#include "../Game.hpp"
#include "Components.hpp"

class GravityComponent : public Component {
public:
  bool isInAir = false;

  float gravityVelocity = 0.3f;
  float jumpVelocity = -5.0f;

  std::shared_ptr<ColliderComponent> collider;
  std::shared_ptr<TransformComponent> transform;

  GravityComponent() = default;

  GravityComponent(float gravityVelocity, float jumpVelocity)
      : gravityVelocity(gravityVelocity), jumpVelocity(jumpVelocity) {}

  void init() override {
    if (!entity->hasComponent<ColliderComponent>()) {
      entity->addComponent<ColliderComponent>("gravity");
    }

    transform = entity->getComponentPtr<TransformComponent>();
    collider = entity->getComponentPtr<ColliderComponent>();
  }

  void update() override {
    transform->velocity.y += this->gravityVelocity;

    for (std::shared_ptr<ColliderComponent> coll : Game::colliders) {
      if (Collision::AABB(*collider, *coll) && (collider->tag != coll->tag)) {

        if (gravityCollision(coll)) {

          transform->position.y =
              coll->entity->getComponent<TransformComponent>().position.y -
              transform->height;

          this->isInAir = false;

          transform->velocity.y = std::min(0.0f, transform->velocity.y);
        }
      }
    }
  }

  bool gravityCollision(std::shared_ptr<ColliderComponent> coll) {
    return coll->tag == "floor_tile" &&
           transform->position.y <=
               coll->entity->getComponent<TransformComponent>().position.y -
                   coll->entity->getComponent<TransformComponent>().height;
  }
};
