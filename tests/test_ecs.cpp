#include "../src/ECS/ECS.hpp"
#include <cassert>
#include <iostream>

static int failures = 0;

#define TEST(name) static void name()
#define RUN(name)                                                              \
  do {                                                                         \
    std::cout << "  " #name "... ";                                            \
    name();                                                                    \
    std::cout << "ok" << std::endl;                                            \
  } while (0)
#define EXPECT(cond)                                                           \
  do {                                                                         \
    if (!(cond)) {                                                             \
      std::cerr << "FAIL at " << __FILE__ << ":" << __LINE__ << ": " #cond    \
                << std::endl;                                                  \
      ++failures;                                                              \
      return;                                                                  \
    }                                                                          \
  } while (0)

class TestComponent : public Component {
public:
  int value = 0;
  bool updated = false;

  TestComponent() = default;
  explicit TestComponent(int v) : value(v) {}

  void update(uint_fast32_t step) override { updated = true; }
};

class OtherComponent : public Component {
public:
  float data = 0.0f;
};

TEST(add_entity) {
  Manager mgr;
  auto &e = mgr.addEntity();
  EXPECT(e.isActive());
}

TEST(destroy_entity) {
  Manager mgr;
  auto &e = mgr.addEntity();
  e.destroy();
  EXPECT(!e.isActive());
}

TEST(add_component) {
  Manager mgr;
  auto &e = mgr.addEntity();
  auto &comp = e.addComponent<TestComponent>(42);
  EXPECT(e.hasComponent<TestComponent>());
  EXPECT(comp.value == 42);
}

TEST(get_component) {
  Manager mgr;
  auto &e = mgr.addEntity();
  e.addComponent<TestComponent>(99);
  auto &comp = e.getComponent<TestComponent>();
  EXPECT(comp.value == 99);
}

TEST(get_component_ptr) {
  Manager mgr;
  auto &e = mgr.addEntity();
  e.addComponent<TestComponent>(55);
  auto ptr = e.getComponentPtr<TestComponent>();
  EXPECT(ptr != nullptr);
  EXPECT(ptr->value == 55);
}

TEST(has_component_false) {
  Manager mgr;
  auto &e = mgr.addEntity();
  EXPECT(!e.hasComponent<TestComponent>());
}

TEST(multiple_components) {
  Manager mgr;
  auto &e = mgr.addEntity();
  e.addComponent<TestComponent>(1);
  e.addComponent<OtherComponent>();
  EXPECT(e.hasComponent<TestComponent>());
  EXPECT(e.hasComponent<OtherComponent>());
  EXPECT(e.getComponent<TestComponent>().value == 1);
}

TEST(entity_update_propagates) {
  Manager mgr;
  auto &e = mgr.addEntity();
  auto &comp = e.addComponent<TestComponent>();
  EXPECT(!comp.updated);
  e.update(10);
  EXPECT(comp.updated);
}

TEST(manager_update_all) {
  Manager mgr;
  auto &e1 = mgr.addEntity();
  auto &e2 = mgr.addEntity();
  auto &c1 = e1.addComponent<TestComponent>();
  auto &c2 = e2.addComponent<TestComponent>();
  mgr.update(10);
  EXPECT(c1.updated);
  EXPECT(c2.updated);
}

TEST(groups) {
  Manager mgr;
  auto &e = mgr.addEntity();
  e.addGroup(0);
  EXPECT(e.hasGroup(0));
  EXPECT(!e.hasGroup(1));

  auto &group = mgr.getGroup(0);
  EXPECT(group.size() == 1);
  EXPECT(group[0] == &e);
}

TEST(del_group) {
  Manager mgr;
  auto &e = mgr.addEntity();
  e.addGroup(0);
  EXPECT(e.hasGroup(0));
  e.delGroup(0);
  EXPECT(!e.hasGroup(0));
}

TEST(refresh_removes_inactive_entities) {
  Manager mgr;
  auto &e1 = mgr.addEntity();
  auto &e2 = mgr.addEntity();
  e1.addGroup(0);
  e2.addGroup(0);

  e1.destroy();
  mgr.refresh();

  auto &group = mgr.getGroup(0);
  EXPECT(group.size() == 1);
}

TEST(refresh_removes_degrouped_entities) {
  Manager mgr;
  auto &e = mgr.addEntity();
  e.addGroup(0);

  auto &group = mgr.getGroup(0);
  EXPECT(group.size() == 1);

  e.delGroup(0);
  mgr.refresh();

  EXPECT(group.empty());
}

TEST(component_init_called) {
  Manager mgr;
  auto &e = mgr.addEntity();

  class InitComponent : public Component {
  public:
    bool initCalled = false;
    void init() override { initCalled = true; }
  };

  auto &comp = e.addComponent<InitComponent>();
  EXPECT(comp.initCalled);
}

TEST(component_entity_pointer) {
  Manager mgr;
  auto &e = mgr.addEntity();
  auto &comp = e.addComponent<TestComponent>();
  EXPECT(comp.entity == &e);
}

int main() {
  std::cout << "ECS tests:" << std::endl;

  RUN(add_entity);
  RUN(destroy_entity);
  RUN(add_component);
  RUN(get_component);
  RUN(get_component_ptr);
  RUN(has_component_false);
  RUN(multiple_components);
  RUN(entity_update_propagates);
  RUN(manager_update_all);
  RUN(groups);
  RUN(del_group);
  RUN(refresh_removes_inactive_entities);
  RUN(refresh_removes_degrouped_entities);
  RUN(component_init_called);
  RUN(component_entity_pointer);

  if (failures > 0) {
    std::cerr << failures << " test(s) FAILED" << std::endl;
    return 1;
  }
  std::cout << "All ECS tests passed." << std::endl;
  return 0;
}
