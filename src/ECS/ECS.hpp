#pragma once
#include <algorithm>
#include <array>
#include <bitset>
#include <memory>
#include <vector>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID() {
  static ComponentID lastID = 0u;
  return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
  static ComponentID typeID = getNewComponentTypeID();
  return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<std::shared_ptr<Component>, maxComponents>;

class Component {
public:
  Entity *entity;

  virtual void init() {}
  virtual void update(uint_fast32_t step) {}
  virtual void draw() {}

  virtual ~Component() {}
};

class Entity {
private:
  Manager &manager;

  bool active = true;
  std::vector<std::shared_ptr<Component>> components;

  ComponentArray componentArray;
  ComponentBitSet componentBitSet;
  GroupBitSet groupBitSet;

public:
  Entity(Manager &mManager) : manager(mManager) {}

  void update(uint_fast32_t step) {
    for (auto &c : components)
      c->update(step);
  }

  void draw() {
    for (auto &c : components)
      c->draw();
  }

  bool isActive() const { return active; }
  void destroy() { active = false; }

  bool hasGroup(Group mGroup) const { return groupBitSet[mGroup]; }

  void addGroup(Group mGroup);
  void delGroup(Group mGroup) { groupBitSet[mGroup] = false; }

  template <typename T> bool hasComponent() const {
    return componentBitSet[getComponentTypeID<T>()];
  }

  template <typename T, typename... TArgs> T &addComponent(TArgs &&...mArgs) {
    std::shared_ptr<T> component_ptr =
        std::make_shared<T>(std::forward<TArgs>(mArgs)...);
    component_ptr->entity = this;

    components.emplace_back(component_ptr);

    componentArray[getComponentTypeID<T>()] = component_ptr;
    componentBitSet[getComponentTypeID<T>()] = true;

    component_ptr->init();
    return *component_ptr;
  }

  template <typename T> T &getComponent() const {
    return *std::dynamic_pointer_cast<T>(
        componentArray[getComponentTypeID<T>()]);
  }

  template <typename T> std::shared_ptr<T> getComponentPtr() const {
    return std::dynamic_pointer_cast<T>(
        componentArray[getComponentTypeID<T>()]);
  }
};

class Manager {
private:
  std::vector<std::shared_ptr<Entity>> entities;
  std::array<std::vector<Entity *>, maxGroups> groupedEntities;

public:
  void update(uint_fast32_t step) {
    for (auto &e : entities)
      e->update(step);
  }
  void draw() {
    for (auto &e : entities)
      e->draw();
  }

  void refresh() {
    for (uint_fast32_t i = 0; i > maxGroups; i++) {
      auto &v(groupedEntities[i]);

      v.erase(std::remove_if(std::begin(v), std::end(v),
                             [i](Entity *&mEntity) {
                               return !mEntity->hasGroup(i) ||
                                      !mEntity->isActive();
                             }),
              std::end(v));
    }

    entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                                  [](const std::shared_ptr<Entity> &mEntity) {
                                    return !mEntity->isActive();
                                  }),
                   std::end(entities));
  }

  Entity &addEntity() {
    entities.emplace_back(std::make_shared<Entity>(*this));
    return *entities.back();
  }

  void addGroup(Entity *mEntity, Group mGroup) {
    groupedEntities[mGroup].emplace_back(mEntity);
  }

  std::vector<Entity *> &getGroup(Group mGroup) {
    return groupedEntities[mGroup];
  }
};
