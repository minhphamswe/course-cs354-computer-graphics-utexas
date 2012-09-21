#ifndef CORE_VECTOR_H_
#define CORE_VECTOR_H_

class Point;

class Vector {
 public:
  float x, y, z;

 public:
  Vector();
  Vector(float xx, float yy);
  Vector(float xx, float yy, float zz);

  // Operations with scalars
  /// Multiply with scalar and return new Vector
  Vector operator*(float f) const;

  /// Multiply with scalar and save to this Vector
  Vector& operator*=(float f);

  // Operations with vectors
  Vector operator+(const Vector& v) const;
  Vector& operator+=(const Vector& v);

  Vector operator-(const Vector& v) const;
  Vector& operator-=(const Vector& v);

  float operator[](int i) const;
};

Vector operator*(float f, const Vector& v);

#endif
