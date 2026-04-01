#pragma once

#include "../Game.hpp"
#include "Components.hpp"

class GravityComponent;

class KeyboardController : public Component {
public:
  void init() override;
  void update(uint_fast32_t step) override;

private:
  std::shared_ptr<TransformComponent> transform;
  std::shared_ptr<GravityComponent> gravity;
};
