#include "../src/Collision.hpp"
#include "../src/ECS/ColliderComponent.hpp"
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

TEST(overlapping_rects) {
  SDL_Rect a{0, 0, 50, 50};
  SDL_Rect b{25, 25, 50, 50};
  EXPECT(Collision::AABB(a, b));
}

TEST(non_overlapping_rects) {
  SDL_Rect a{0, 0, 50, 50};
  SDL_Rect b{100, 100, 50, 50};
  EXPECT(!Collision::AABB(a, b));
}

TEST(touching_edge) {
  SDL_Rect a{0, 0, 50, 50};
  SDL_Rect b{50, 0, 50, 50};
  EXPECT(Collision::AABB(a, b));
}

TEST(same_rect) {
  SDL_Rect a{10, 10, 30, 30};
  EXPECT(Collision::AABB(a, a));
}

TEST(one_inside_other) {
  SDL_Rect outer{0, 0, 100, 100};
  SDL_Rect inner{25, 25, 10, 10};
  EXPECT(Collision::AABB(outer, inner));
  EXPECT(Collision::AABB(inner, outer));
}

TEST(separated_horizontally) {
  SDL_Rect a{0, 0, 10, 10};
  SDL_Rect b{20, 0, 10, 10};
  EXPECT(!Collision::AABB(a, b));
}

TEST(separated_vertically) {
  SDL_Rect a{0, 0, 10, 10};
  SDL_Rect b{0, 20, 10, 10};
  EXPECT(!Collision::AABB(a, b));
}

TEST(zero_size_rect) {
  SDL_Rect a{5, 5, 0, 0};
  SDL_Rect b{0, 0, 10, 10};
  EXPECT(Collision::AABB(a, b));
}

int main() {
  std::cout << "Collision tests:" << std::endl;

  RUN(overlapping_rects);
  RUN(non_overlapping_rects);
  RUN(touching_edge);
  RUN(same_rect);
  RUN(one_inside_other);
  RUN(separated_horizontally);
  RUN(separated_vertically);
  RUN(zero_size_rect);

  if (failures > 0) {
    std::cerr << failures << " test(s) FAILED" << std::endl;
    return 1;
  }
  std::cout << "All Collision tests passed." << std::endl;
  return 0;
}
