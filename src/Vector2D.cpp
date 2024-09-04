#include "Vector2D.hpp"
#include "math.h"

Vector2D::Vector2D() {
  x = 0.0f;
  y = 0.0f;
}

Vector2D::Vector2D(float x, float y) {
  this->x = x;
  this->y = y;
}

Vector2D &Vector2D::Add(const Vector2D &vec) {
  this->x += vec.x;
  this->y += vec.y;
  return *this;
}

Vector2D &Vector2D::Subtract(const Vector2D &vec) {
  this->x -= vec.x;
  this->y -= vec.y;
  return *this;
}

Vector2D &Vector2D::Multiply(const Vector2D &vec) {
  this->x *= vec.x;
  this->y *= vec.y;
  return *this;
}

Vector2D &Vector2D::Divide(const Vector2D &vec) {
  this->x /= vec.x;
  this->y /= vec.y;
  return *this;
}

Vector2D &operator+(Vector2D &v1, const Vector2D &v2) { return v1.Add(v2); }
Vector2D &operator-(Vector2D &v1, const Vector2D &v2) {
  return v1.Subtract(v2);
}

Vector2D &operator*(Vector2D &v1, const Vector2D &v2) {
  return v1.Multiply(v2);
}

Vector2D &operator/(Vector2D &v1, const Vector2D &v2) { return v1.Divide(v2); }

Vector2D &Vector2D::operator+=(const Vector2D &vec) { return this->Add(vec); }
Vector2D &Vector2D::operator-=(const Vector2D &vec) {
  return this->Subtract(vec);
}

Vector2D &Vector2D::operator*=(const Vector2D &vec) {
  return this->Multiply(vec);
}

Vector2D &Vector2D::operator/=(const Vector2D &vec) {
  return this->Divide(vec);
}

Vector2D &Vector2D::operator*(const int_fast32_t &i) {
  this->x *= i;
  this->y *= i;

  return *this;
}

Vector2D &Vector2D::Zero() {
  this->x = 0.0f;
  this->y = 0.0f;

  return *this;
}

Vector2D &Vector2D::Normalize() {
  float length = sqrt(x * x + y * y);

  if (length != 0.0f) {
    this->x /= length;
    this->y /= length;
  }

  return *this;
}

std::ostream &operator<<(std::ostream &stream, const Vector2D &vec) {
  stream << "(" << vec.x << "," << vec.y << ")";
  return stream;
}

bool operator==(const Vector2D &v1, const Vector2D &v2) {
  if (v1.x == v2.x && v1.y == v2.y) {
    return true;
  } else {
    return false;
  }
}

bool operator!=(const Vector2D &v1, const Vector2D &v2) {
  if (v1 == v2) {
    return false;
  } else {
    return true;
  }
}