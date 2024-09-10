#pragma once

#include "../Game.hpp"
#include "Components.hpp"

class KeyboardController : public Component {
public:
  std::shared_ptr<TransformComponent> transform;
  std::shared_ptr<GravityComponent> gravity;

  void init() override;

  void update() override;
};
