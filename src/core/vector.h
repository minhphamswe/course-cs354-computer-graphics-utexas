#ifndef CORE_VECTOR_H_
#define CORE_VECTOR_H_

class Point;

class Vector {
public:
  float x, y, z;

public:
  Vector();
  Vector(float xx, float yy, float zz);

  // Operations with scalars
  /** Return the multiple of this Vector with a scalar without modifying this. */
  Vector operator*(float f) const;
  /** Multiply this Vector */
  Vector& operator*=(float f);

  // Operations with vectors
  Vector operator+(const Vector& v) const;
  Vector& operator+=(const Vector& v);

  Vector operator-(const Vector& v) const;
  Vector& operator-=(const Vector& v);

};

#endif