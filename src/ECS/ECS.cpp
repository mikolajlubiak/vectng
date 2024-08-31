#include "ECS.hpp"

void Entity::addGroup(Group mGroup) {
  groupBitSet[mGroup] = true;
  manager.addGroup(this, mGroup);
}