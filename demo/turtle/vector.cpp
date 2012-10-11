#include "./common.h"
#include "./vector.h"

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

float Vector::operator[](int i) const {
  Assert(i >= 0);
  Assert(i < 3);
  return (&x)[i];
}
