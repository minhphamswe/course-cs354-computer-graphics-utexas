#ifndef CORE_TRANSFORM_H_
#define CORE_TRANSFORM_H_

namespace ishi {

#include <core/matrix.h>

class Point;
class Vector;

class Transform {
 private:
  Matrix4x4 m, mInv;

 public:
  /// Initialize an identity transform
  Transform();

  /// Initialize a transform with a matrix, calculating its inverse
  explicit Transform(const Matrix4x4 &mat);

  /// Initialize a transform with a matrix and its inverse
  Transform(const Matrix4x4 &mat, const Matrix4x4 &matInv);

  /// Transform a point
  Point operator()(const Point &p) const;

  /// Transform a vector
  Vector operator()(const Vector &v) const;

  /// Concatentate multiple transforms
  Transform operator*(const Transform &t2) const;

  friend Transform Inverse(const Transform &t);
};

/// Return the inverse a transform as a new transform
Transform Inverse(const Transform &t);

/// Return a transform representing a translation by a vector
Transform Translate(const Vector &delta);

/// Return a transform representing a rotation around the X axis
Transform RotateX(float angle);

/// Return a transform representing a rotation around the Y axis
Transform RotateY(float angle);

/// Return a transform representing a rotation around the Z axis
Transform RotateZ(float angle);

/// Return a transform representing a rotation around an arbitrary axis
Transform Rotate(float angle, const Vector &axis);

/// Return a transform representing a general scaling in each of the axes
Transform Scale(float x, float y, float z);

}  // namespace ishi

#endif
