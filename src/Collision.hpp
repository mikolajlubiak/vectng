#pragma once

#include <SDL2/SDL.h>
#include <memory>

class ColliderComponent;

class Collision {
public:
  // Touching edges count as collision (>=)
  static bool AABB(const SDL_Rect &rectA, const SDL_Rect &rectB);
  static bool AABB(const ColliderComponent &collA,
                   const ColliderComponent &collB);
  static bool AABB(const std::shared_ptr<ColliderComponent> &collA,
                   const std::shared_ptr<ColliderComponent> &collB);

  // Strict overlap only — touching edges do NOT count (>)
  static bool Overlap(const SDL_Rect &rectA, const SDL_Rect &rectB);
};
