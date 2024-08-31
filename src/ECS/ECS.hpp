#pragma once
#include <algorithm>
#include <array>
#include <bitset>
#include <memory>
#include <vector>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
  static ComponentID lastID = 0;
  return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
  static ComponentID typeID = getComponentTypeID();
  return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<std::shared_ptr<Component>, maxComponents>;

class Component {
public:
  Entity *entity;

  virtual void init() {}
  virtual void update() {}
  virtual void draw() {}

  virtual ~Component() {}
};

class Entity {
private:
  bool active = true;
  std::vector<std::shared_ptr<Component>> components;

  ComponentArray componentArray;
  ComponentBitSet componentBitSet;

public:
  void update() {
    for (auto &c : components)
      c->update();
  }
  void draw() {
    for (auto &c : components)
      c->draw();
  }
  bool isActive() const { return active; }
  void destroy() { active = false; }

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
  std::vector<std::unique_ptr<Entity>> entities;

public:
  void update() {
    for (auto &e : entities)
      e->update();
  }
  void draw() {
    for (auto &e : entities)
      e->draw();
  }

  void refresh() {
    entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                                  [](const std::unique_ptr<Entity> &mEntity) {
                                    return !mEntity->isActive();
                                  }),
                   std::end(entities));
  }

  Entity &addEntity() {
    entities.emplace_back(std::make_unique<Entity>());
    return *entities.back();
  }
};
