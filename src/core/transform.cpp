#include <core/transform.h>
#include <core/matrix.h>
#include <core/vector.h>
#include <core/point.h>

Transform::Transform()
    : m(Matrix4x4()), mInv(Matrix4x4()) {}

Transform::Transform(const Matrix4x4& mat)
    : m(mat), mInv(Inverse(mat)) {}

Transform::Transform(const Matrix4x4& mat, const Matrix4x4& matInv)
    : m(mat), mInv(matInv) {}

inline Point Transform::operator()(const Point& p) const {
  float x = p.x, y = p.y, z = p.z;
  // Implicitly convert point to homogeneous coordinates
  float xp = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
  float yp = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
  float zp = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
  float wp = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];
  // Implicitly convert point back to non-homogeneous coordinates
  if (wp == 1.f)
    return Point(xp, yp, zp);
  else
    return Point(xp, yp, zp) * (1/wp);
}

inline Vector Transform::operator()(const Vector& v) const {
  float x = v.x, y = v.y, z = v.z;
  return Vector(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
                m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
                m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
}

Transform Transform::operator*(const Transform& t2) const
{

}

Transform Inverse(const Transform& t)
{

}


Transform Translate(const Vector& delta)
{

}

Transform RotateX(float angle)
{

}

Transform RotateY(float angle)
{

}

Transform RotateZ(float angle)
{

}

Transform Rotate(float angle, const Vector& axis)
{

}

Transform Scale(float x, float y, float z)
{

}
