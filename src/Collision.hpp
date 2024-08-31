#pragma once

#include <SDL2/SDL.h>

class ColliderComponent;

class Collision {
public:
  static bool AABB(const SDL_Rect &rectA, const SDL_Rect &rectB);
  static bool AABB(const ColliderComponent &collA,
                   const ColliderComponent &collB);
};