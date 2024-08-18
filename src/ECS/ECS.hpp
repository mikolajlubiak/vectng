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
using ComponentArray = std::array<Component *, maxComponents>;

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
	std::vector<std::unique_ptr<Component>> components;

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
		// Create a unique_ptr for the component
		std::shared_ptr<T> uPtr = std::make_unique<T>(std::forward<TArgs>(mArgs)...);
		uPtr->entity = this;

		// Store the unique_ptr in the components vector
		components.emplace_back(std::move(uPtr));

		// Get the raw pointer from the unique_ptr and cast it to the correct type
		T *c = static_cast<T*>(components.back().get());

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template <typename T> T &getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T *>(ptr);
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
		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity) { return !mEntity->isActive(); }), std::end(entities));
	}

	Entity &addEntity() {
    	entities.emplace_back(std::make_unique<Entity>());
    	return *entities.back();
	}
};
