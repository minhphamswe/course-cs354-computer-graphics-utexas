#ifndef CORE_POINT_H_
#define CORE_POINT_H_

class Vector;

class Point {
public:
  float x, y, z;

public:
  Point();
  Point(float xx, float yy);
  Point(float xx, float yy, float zz);

  Point operator+(const Vector& v) const;
  Point& operator+=(const Vector& v);

  Point operator-(const Vector& v) const;
  Point& operator-=(const Vector& v);

  float operator[](int i) const;
};

#endif
