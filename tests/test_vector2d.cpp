#include "../src/Vector2D.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>

static constexpr float kEpsilon = 1e-5f;

static bool near(float a, float b) { return std::fabs(a - b) < kEpsilon; }

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

TEST(default_constructor) {
  Vector2D v;
  EXPECT(v.x == 0.0f);
  EXPECT(v.y == 0.0f);
}

TEST(parameterized_constructor) {
  Vector2D v(3.0f, 4.0f);
  EXPECT(near(v.x, 3.0f));
  EXPECT(near(v.y, 4.0f));
}

TEST(add) {
  Vector2D a(1.0f, 2.0f);
  Vector2D b(3.0f, 4.0f);
  Vector2D result = a.Add(b);
  EXPECT(near(result.x, 4.0f));
  EXPECT(near(result.y, 6.0f));
}

TEST(subtract) {
  Vector2D a(10.0f, 20.0f);
  Vector2D b(3.0f, 5.0f);
  Vector2D result = a.Subtract(b);
  EXPECT(near(result.x, 7.0f));
  EXPECT(near(result.y, 15.0f));
}

TEST(subtract_negative_result) {
  Vector2D a(1.0f, 1.0f);
  Vector2D b(5.0f, 10.0f);
  Vector2D result = a.Subtract(b);
  EXPECT(near(result.x, -4.0f));
  EXPECT(near(result.y, -9.0f));
}

TEST(multiply) {
  Vector2D a(2.0f, 3.0f);
  Vector2D b(4.0f, 5.0f);
  Vector2D result = a.Multiply(b);
  EXPECT(near(result.x, 8.0f));
  EXPECT(near(result.y, 15.0f));
}

TEST(divide) {
  Vector2D a(10.0f, 20.0f);
  Vector2D b(2.0f, 5.0f);
  Vector2D result = a.Divide(b);
  EXPECT(near(result.x, 5.0f));
  EXPECT(near(result.y, 4.0f));
}

TEST(operator_plus) {
  Vector2D a(1.0f, 2.0f);
  Vector2D b(3.0f, 4.0f);
  Vector2D result = a + b;
  EXPECT(near(result.x, 4.0f));
  EXPECT(near(result.y, 6.0f));
}

TEST(operator_minus) {
  Vector2D a(10.0f, 8.0f);
  Vector2D b(3.0f, 2.0f);
  Vector2D result = a - b;
  EXPECT(near(result.x, 7.0f));
  EXPECT(near(result.y, 6.0f));
}

TEST(operator_multiply_vec) {
  Vector2D a(2.0f, 3.0f);
  Vector2D b(4.0f, 5.0f);
  Vector2D result = a * b;
  EXPECT(near(result.x, 8.0f));
  EXPECT(near(result.y, 15.0f));
}

TEST(operator_divide_vec) {
  Vector2D a(10.0f, 9.0f);
  Vector2D b(2.0f, 3.0f);
  Vector2D result = a / b;
  EXPECT(near(result.x, 5.0f));
  EXPECT(near(result.y, 3.0f));
}

TEST(operator_multiply_scalar_right) {
  Vector2D v(3.0f, 4.0f);
  Vector2D result = v * 2.0f;
  EXPECT(near(result.x, 6.0f));
  EXPECT(near(result.y, 8.0f));
}

TEST(operator_multiply_scalar_left) {
  Vector2D v(3.0f, 4.0f);
  Vector2D result = 2.0f * v;
  EXPECT(near(result.x, 6.0f));
  EXPECT(near(result.y, 8.0f));
}

TEST(operator_plus_equals) {
  Vector2D a(1.0f, 2.0f);
  Vector2D b(3.0f, 4.0f);
  a += b;
  EXPECT(near(a.x, 4.0f));
  EXPECT(near(a.y, 6.0f));
}

TEST(operator_minus_equals) {
  Vector2D a(10.0f, 8.0f);
  Vector2D b(3.0f, 2.0f);
  a -= b;
  EXPECT(near(a.x, 7.0f));
  EXPECT(near(a.y, 6.0f));
}

TEST(operator_multiply_equals) {
  Vector2D a(2.0f, 3.0f);
  Vector2D b(4.0f, 5.0f);
  a *= b;
  EXPECT(near(a.x, 8.0f));
  EXPECT(near(a.y, 15.0f));
}

TEST(operator_divide_equals) {
  Vector2D a(10.0f, 9.0f);
  Vector2D b(2.0f, 3.0f);
  a /= b;
  EXPECT(near(a.x, 5.0f));
  EXPECT(near(a.y, 3.0f));
}

TEST(operator_equals) {
  Vector2D a(1.0f, 2.0f);
  Vector2D b(1.0f, 2.0f);
  Vector2D c(3.0f, 4.0f);
  EXPECT(a == b);
  EXPECT(!(a == c));
}

TEST(operator_not_equals) {
  Vector2D a(1.0f, 2.0f);
  Vector2D b(3.0f, 4.0f);
  EXPECT(a != b);
}

TEST(zero) {
  Vector2D v(5.0f, 10.0f);
  v.Zero();
  EXPECT(v.x == 0.0f);
  EXPECT(v.y == 0.0f);
}

TEST(normalize) {
  Vector2D v(3.0f, 4.0f);
  v.Normalize();
  EXPECT(near(v.x, 0.6f));
  EXPECT(near(v.y, 0.8f));
  float length = std::sqrt(v.x * v.x + v.y * v.y);
  EXPECT(near(length, 1.0f));
}

TEST(normalize_zero_vector) {
  Vector2D v(0.0f, 0.0f);
  v.Normalize();
  EXPECT(v.x == 0.0f);
  EXPECT(v.y == 0.0f);
}

TEST(stream_output) {
  Vector2D v(1.5f, 2.5f);
  std::ostringstream oss;
  oss << v;
  EXPECT(oss.str() == "(1.5,2.5)");
}

TEST(subtract_is_not_commutative) {
  Vector2D a(10.0f, 20.0f);
  Vector2D b(3.0f, 5.0f);
  Vector2D ab = a - b;
  Vector2D ba = b - a;
  EXPECT(near(ab.x, 7.0f));
  EXPECT(near(ab.y, 15.0f));
  EXPECT(near(ba.x, -7.0f));
  EXPECT(near(ba.y, -15.0f));
}

TEST(operator_plus_with_temporary) {
  Vector2D result = Vector2D(1.0f, 2.0f) + Vector2D(3.0f, 4.0f);
  EXPECT(near(result.x, 4.0f));
  EXPECT(near(result.y, 6.0f));
}

int main() {
  std::cout << "Vector2D tests:" << std::endl;

  RUN(default_constructor);
  RUN(parameterized_constructor);
  RUN(add);
  RUN(subtract);
  RUN(subtract_negative_result);
  RUN(multiply);
  RUN(divide);
  RUN(operator_plus);
  RUN(operator_minus);
  RUN(operator_multiply_vec);
  RUN(operator_divide_vec);
  RUN(operator_multiply_scalar_right);
  RUN(operator_multiply_scalar_left);
  RUN(operator_plus_equals);
  RUN(operator_minus_equals);
  RUN(operator_multiply_equals);
  RUN(operator_divide_equals);
  RUN(operator_equals);
  RUN(operator_not_equals);
  RUN(zero);
  RUN(normalize);
  RUN(normalize_zero_vector);
  RUN(stream_output);
  RUN(subtract_is_not_commutative);
  RUN(operator_plus_with_temporary);

  if (failures > 0) {
    std::cerr << failures << " test(s) FAILED" << std::endl;
    return 1;
  }
  std::cout << "All Vector2D tests passed." << std::endl;
  return 0;
}
