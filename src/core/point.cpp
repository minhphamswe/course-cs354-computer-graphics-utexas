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
    
float Point::operator[](int i) const {
  Assert(i >= 0);
  Assert(i < 3);
  return (&x)[i];  
}