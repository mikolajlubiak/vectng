#include "Collision.hpp"
#include "ECS/Components.hpp"

bool Collision::AABB(const SDL_Rect &rectA, const SDL_Rect &rectB) {
  if (rectA.x + rectA.w >= rectB.x && rectB.x + rectB.w >= rectA.x &&
      rectA.y + rectA.h >= rectB.y && rectB.y + rectB.h >= rectA.y) {
    return true;
  } else {
    return false;
  }
}

bool Collision::AABB(const ColliderComponent &collA,
                     const ColliderComponent &collB) {
  if (AABB(collA.collider, collB.collider)) {
    return true;
  } else {
    return false;
  }
}

bool Collision::AABB(const std::shared_ptr<ColliderComponent> collA,
                     const std::shared_ptr<ColliderComponent> collB) {
  if (AABB(collA->collider, collB->collider)) {
    return true;
  } else {
    return false;
  }
}