#include "Vector2D.hpp"
#include <cmath>

Vector2D::Vector2D() : x(0.0f), y(0.0f) {}

Vector2D::Vector2D(float x, float y) : y(y), x(x) {}

auto Vector2D::Add(const Vector2D &vec) const -> Vector2D {
  return Vector2D(vec.x + this->x, vec.y + this->y);
}

auto Vector2D::Subtract(const Vector2D &vec) const -> Vector2D {
  return Vector2D(vec.x - this->x, vec.y - this->y);
}

auto Vector2D::Multiply(const Vector2D &vec) const -> Vector2D {
  return Vector2D(vec.x * this->x, vec.y * this->y);
}

auto Vector2D::Divide(const Vector2D &vec) const -> Vector2D {
  return Vector2D(this->x / vec.x, this->y / vec.y);
}

auto operator+(const Vector2D &v1, const Vector2D &v2) -> Vector2D {
  return v1.Add(v2);
}

auto operator-(const Vector2D &v1, const Vector2D &v2) -> Vector2D {
  return v1.Subtract(v2);
}

auto operator*(const Vector2D &v1, const Vector2D &v2) -> Vector2D {
  return v1.Multiply(v2);
}

auto operator/(const Vector2D &v1, const Vector2D &v2) -> Vector2D {
  return v1.Divide(v2);
}

Vector2D &Vector2D::operator+=(const Vector2D &vec) {
  *this = this->Add(vec);
  return *this;
}
Vector2D &Vector2D::operator-=(const Vector2D &vec) {
  *this = this->Subtract(vec);
  return *this;
}

Vector2D &Vector2D::operator*=(const Vector2D &vec) {
  *this = this->Multiply(vec);
  return *this;
}

Vector2D &Vector2D::operator/=(const Vector2D &vec) {
  *this = this->Divide(vec);
  return *this;
}

auto Vector2D::operator*(const int_fast32_t &i) const -> Vector2D {
  Vector2D v{};

  v.x = this->x * static_cast<float>(i);
  v.y = this->y * static_cast<float>(i);

  return v;
}

auto Vector2D::Zero() -> void {
  this->x = 0.0f;
  this->y = 0.0f;
}

auto Vector2D::Normalize() -> void {
  float length = sqrtf(x * x + y * y);

  if (length != 0.0f) {
    this->x /= length;
    this->y /= length;
  }
}

auto operator<<(std::ostream &stream, const Vector2D &vec) -> std::ostream & {
  stream << "(" << vec.x << "," << vec.y << ")";
  return stream;
}

auto operator==(const Vector2D &v1, const Vector2D &v2) -> bool {
  return v1.x == v2.x && v1.y == v2.y;
}

auto operator!=(const Vector2D &v1, const Vector2D &v2) -> bool {
  return !(v1 == v2);
}