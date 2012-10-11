#ifndef CORE_VECTOR_H_
#define CORE_VECTOR_H_

class Point;

class Vector {
 public:
  /// Vector components
  float x, y, z;

 public:
  /// Initialize zero vector
  Vector();

  /// Initialize vector on the xy plane
  Vector(float xx, float yy);

  /// Initialize a full 3D vector
  Vector(float xx, float yy, float zz);

  /// Multiply with scalar and return new Vector
  Vector operator*(float f) const;

  /// Multiply with scalar and save to this Vector
  Vector& operator*=(float f);

  /// Add to another Vector and return a new Vector
  Vector operator+(const Vector& v) const;

  /// Add to another Vector and save to this Vector
  Vector& operator+=(const Vector& v);

  /// Subtract another Vector and return a new Vector
  Vector operator-(const Vector& v) const;

  /// Subtract another Vector and save to this Vector
  Vector& operator-=(const Vector& v);

  /// Get Vector components by integer index
  float operator[](int i) const;
};

/// Multiply with a scalar and return new Vector (when scalar comes first)
Vector operator*(float f, const Vector& v);

#endif
