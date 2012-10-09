#include <core/vector.h>
#include <core/common.h>

namespace ishi {

/// Initialize all components set to 0
Vector::Vector()
    : x(0), y(0), z(0) {}

/// Initialize x, y components to passed-in values, z to 0
Vector::Vector(float xx, float yy)
    : x(xx), y(yy), z(0) {}

/// Initialize x, y, z components to passed-in values
Vector::Vector(float xx, float yy, float zz)
    : x(xx), y(yy), z(zz) {}

/// Multiply with another vector components wise and initialize a new Vector
/// with the result.
Vector Vector::operator*(float f) const {
  return Vector(x * f, y * f, z * f);
}

/// Multiply
Vector& Vector::operator*=(float f) {
  x *= f;
  y *= f;
  z *= f;
  return *this;
}

Vector operator*(float f, const Vector& v) {
  return Vector(v.x * f, v.y * f, v.z * f);
}

Vector Vector::operator+(const Vector& v) const {
  return Vector(x + v.x, y + v.y, z + v.z);
}

Vector& Vector::operator+=(const Vector& v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

Vector Vector::operator-(const Vector& v) const {
  return Vector(x - v.x, y - v.y, z - v.z);
}

Vector& Vector::operator-=(const Vector& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

Vector Vector::operator-() const {
  return Vector(-x, -y, -z);
}

bool Vector::operator==(const Vector& v) const {
  return ((x == v.x) && (y == v.y) && (z == v.z));
}

float Vector::operator[](int i) const {
  Assert(i >= 0);
  Assert(i < 3);
  return (&x)[i];
}

float Dot(const Vector &v1, const Vector &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector Cross(const Vector &v1, const Vector &v2) {
  return Vector(v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x);
}

float Length(const Vector& v) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}

Vector Normalize(const Vector& v) {
  float l = Length(v);
  if (l) {
    float f = 1/l;
    return Vector(v.x * f, v.y * f, v.z * f);
  } else {
    return Vector();
  }
}

}  // namespace ishi
