#include "GravityComponent.hpp"

void GravityComponent::init() {
  if (!entity->hasComponent<ColliderComponent>()) {
    entity->addComponent<ColliderComponent>("physics");
  }

  transform = entity->getComponentPtr<TransformComponent>();
  collider = entity->getComponentPtr<ColliderComponent>();
}

void GravityComponent::update(uint_fast32_t step) {
  // Apply gravity acceleration
  transform->velocity.y += gravityVelocity;

  float dt = static_cast<float>(step) * transform->speed;

  // Sweep X: move horizontally, sync collider, resolve horizontal collisions
  transform->position.x += transform->velocity.x * dt;
  collider->sync();
  resolveX();

  // Sweep Y: move vertically, sync collider, resolve vertical collisions
  transform->position.y += transform->velocity.y * dt;
  collider->sync();
  resolveY();

  // Final sync so collider matches resolved position
  collider->sync();

  // Ground probe: check 1 pixel below to reliably detect grounded state.
  // This prevents isInAir from oscillating due to float→int truncation
  // when the entity sits exactly on a tile edge.
  isInAir = !checkGrounded();
}

void GravityComponent::resolveX() {
  for (const auto &coll : Game::colliders) {
    if (coll.get() == collider.get()) {
      continue;
    }
    if (coll->tag != FLOOR_TILE_TAG) {
      continue;
    }
    if (!Collision::Overlap(collider->collider, coll->collider)) {
      continue;
    }

    const SDL_Rect &tile = coll->collider;

    if (transform->velocity.x > 0.0f) {
      // Moving right — push to left edge of tile
      transform->position.x =
          static_cast<float>(tile.x) -
          static_cast<float>(collider->collider.w);
    } else if (transform->velocity.x < 0.0f) {
      // Moving left — push to right edge of tile
      transform->position.x = static_cast<float>(tile.x + tile.w);
    }

    transform->velocity.x = 0.0f;
    collider->sync();
  }
}

void GravityComponent::resolveY() {
  for (const auto &coll : Game::colliders) {
    if (coll.get() == collider.get()) {
      continue;
    }
    if (coll->tag != FLOOR_TILE_TAG) {
      continue;
    }
    if (!Collision::Overlap(collider->collider, coll->collider)) {
      continue;
    }

    const SDL_Rect &tile = coll->collider;

    if (transform->velocity.y >= 0.0f) {
      // Moving down or stationary — land on top of tile
      transform->position.y =
          static_cast<float>(tile.y) -
          static_cast<float>(collider->collider.h);
    } else {
      // Moving up — hit bottom of tile (ceiling)
      transform->position.y = static_cast<float>(tile.y + tile.h);
    }

    transform->velocity.y = 0.0f;
    collider->sync();
  }
}

bool GravityComponent::checkGrounded() const {
  // Extend collider 1 pixel downward to detect ground contact,
  // even when the entity bottom exactly touches the tile top.
  SDL_Rect probe = collider->collider;
  probe.h += 1;

  for (const auto &coll : Game::colliders) {
    if (coll.get() == collider.get()) {
      continue;
    }
    if (coll->tag != FLOOR_TILE_TAG) {
      continue;
    }
    if (Collision::Overlap(probe, coll->collider)) {
      return true;
    }
  }
  return false;
}
