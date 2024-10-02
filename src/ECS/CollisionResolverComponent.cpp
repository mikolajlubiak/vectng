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
      auto transform = this->entity->getComponentPtr<TransformComponent>();

      if (this->entity->hasComponent<GravityComponent>()) {
        if (!this->entity->getComponent<GravityComponent>().gravityCollision(
                coll)) {

          if ((transform->position.x +
               static_cast<float>(transform->width) / 2) -
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
      } else {
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

        if ((transform->position.y +
             static_cast<float>(transform->height) / 2) -
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
    }
  }
}
