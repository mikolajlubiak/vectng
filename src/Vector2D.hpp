#pragma once
#include <cstdint>
#include <iostream>

class Vector2D {
public:
  float x;
  float y;

  Vector2D();
  Vector2D(float x, float y);

  auto Add(const Vector2D &vec) const -> Vector2D;
  auto Subtract(const Vector2D &vec) const -> Vector2D;
  auto Multiply(const Vector2D &vec) const -> Vector2D;
  auto Divide(const Vector2D &vec) const -> Vector2D;

  friend auto operator+(Vector2D &v1, const Vector2D &v2) -> Vector2D;
  friend auto operator-(Vector2D &v1, const Vector2D &v2) -> Vector2D;
  friend auto operator*(Vector2D &v1, const Vector2D &v2) -> Vector2D;
  friend auto operator/(Vector2D &v1, const Vector2D &v2) -> Vector2D;
  friend auto operator==(const Vector2D &v1, const Vector2D &v2) -> bool;
  friend auto operator!=(const Vector2D &v1, const Vector2D &v2) -> bool;

  auto operator+=(const Vector2D &vec) -> Vector2D &;
  auto operator-=(const Vector2D &vec) -> Vector2D &;
  auto operator*=(const Vector2D &vec) -> Vector2D &;
  auto operator/=(const Vector2D &vec) -> Vector2D &;

  auto operator*(const int_fast32_t &i) const -> Vector2D;
  auto Zero() -> void;
  auto Normalize() -> void;

  friend auto operator<<(std::ostream &stream,
                         const Vector2D &vec) -> std::ostream &;
};
