#include <core/vector.h>
#include <core/common.h>

Vector::Vector()
    : x(0), y(0), z(0) {}

Vector::Vector(float xx, float yy)
    : x(xx), y(yy), z(0) {}

Vector::Vector(float xx, float yy, float zz)
    : x(xx), y(yy), z(zz) {}

Vector Vector::operator*(float f) const {
  return Vector(x * f, y * f, z * f);
}

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