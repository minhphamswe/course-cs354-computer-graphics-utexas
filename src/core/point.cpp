#include <core/geometry.h>
#include <core/common.h>

Point::Point()
    : x(0), y(0), z(0) {}

Point::Point(float xx, float yy)
    : x(xx), y(yy), z(0) {}

Point::Point(float xx, float yy, float zz)
    : x(xx), y(yy), z(zz) {}

Point Point::operator+(const Vector& v) const {
  return Point(x + v.x, y + v.y, z + v.z);
}

Point& Point::operator+=(const Vector& v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

Point Point::operator-(const Vector& v) const {
  return Point(x - v.x, y - v.y, z - v.z);
}

Point& Point::operator-=(const Vector& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

Vector Point::operator-(const Point& p) const {
  return Vector(x - p.x, y - p.y, z - p.z);
}

Point Point::operator+(const Point& p) const {
  return Point(x + p.x, y + p.y, z + p.z);
}

Point Point::operator*(float f) const {
  return Point(x * f, y * f, z * f);
}

Point operator*(float f, const Point& p) {
  return Point(p.x * f, p.y * f, p.z * f);
}

bool Point::operator==(const Point& p) const {
  return ((x == p.x) && (y == p.y) && (z == p.z));
}

float Point::operator[](int i) const {
  Assert(i >= 0);
  Assert(i < 3);
  return (&x)[i];
}

float Distance(const Point &p1, const Point &p2) {
  return Length(p2-p1);
}
