#ifndef CORE_POINT_H_
#define CORE_POINT_H_

class Vector;

class Point {
public:
  float x, y, z;

public:
  /// Initialize point at origin
  Point();

  /// Initialize point on the x-y plane
  Point(float xx, float yy);

  /// Initialize point in 3 dimensions
  Point(float xx, float yy, float zz);

  /// Add a vector to this point, return a new point
  Point operator+(const Vector& v) const;

  /// Add a vector to this point, return reference to this point
  Point& operator+=(const Vector& v);

  /// Subtract a vector from this point, return a new point
  Point operator-(const Vector& v) const;

  /// Subtract a vector from this point, return reference to this point
  Point& operator-=(const Vector& v);

  /// Get point components by integer index
  float operator[](int i) const;
};

#endif
