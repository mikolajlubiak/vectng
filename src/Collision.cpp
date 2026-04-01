#include "Collision.hpp"
#include "ECS/Components.hpp"

bool Collision::AABB(const SDL_Rect &rectA, const SDL_Rect &rectB) {
  return rectA.x + rectA.w >= rectB.x && rectB.x + rectB.w >= rectA.x &&
         rectA.y + rectA.h >= rectB.y && rectB.y + rectB.h >= rectA.y;
}

bool Collision::AABB(const ColliderComponent &collA,
                     const ColliderComponent &collB) {
  return AABB(collA.collider, collB.collider);
}

bool Collision::AABB(const std::shared_ptr<ColliderComponent> &collA,
                     const std::shared_ptr<ColliderComponent> &collB) {
  return AABB(collA->collider, collB->collider);
}

bool Collision::Overlap(const SDL_Rect &rectA, const SDL_Rect &rectB) {
  return rectA.x < rectB.x + rectB.w && rectA.x + rectA.w > rectB.x &&
         rectA.y < rectB.y + rectB.h && rectA.y + rectA.h > rectB.y;
}
