#include <core/transform.h>

#include <core/common.h>
#include <core/matrix.h>
#include <core/vector.h>
#include <core/point.h>

namespace ishi {

Transform::Transform()
    : m(Matrix4x4()), mInv(Matrix4x4()) {}

Transform::Transform(const Matrix4x4& mat)
    : m(mat), mInv(Inverse(mat)) {}

Transform::Transform(const Matrix4x4& mat, const Matrix4x4& matInv)
    : m(mat), mInv(matInv) {}

Point Transform::operator()(const Point& p) const {
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

Vector Transform::operator()(const Vector& v) const {
  float x = v.x, y = v.y, z = v.z;
  return Vector(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
                m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
                m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
}

Point& Transform::Apply(Point *p) const {
  float x = p->x, y = p->y, z = p->z;

  // Implicitly convert point to homogeneous coordinates
  float xp = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
  float yp = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
  float zp = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
  float wp = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];

  // Implicitly convert point back to non-homogeneous coordinates
  if (wp == 1.f) {
    p->x = xp;
    p->y = yp;
    p->z = zp;
  } else {
    float f = 1/wp;
    p->x = xp * f;
    p->y = yp * f;
    p->z = zp * f;
  }

  return *p;
}

Vector& Transform::Apply(Vector *v) const {
  float x = v->x, y = v->y, z = v->z;
  v->x = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z;
  v->y = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z;
  v->z = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z;
  return *v;
}

Transform Transform::operator*(const Transform& t2) const {
  Matrix4x4 mat = Mul(m, t2.m);
  Matrix4x4 matInv = Mul(t2.mInv, mInv);
  return Transform(mat, matInv);
}

Transform& Transform::operator*=(const ishi::Transform& t2) {
  m = Mul(m, t2.m);
  mInv = Mul(t2.mInv, mInv);
  return *this;
}

Point Transform::Invert(const Point& p) const {
  float x = p.x, y = p.y, z = p.z;

  // Implicitly convert point to homogeneous coordinates
  float xp = mInv.m[0][0]*x + mInv.m[0][1]*y + mInv.m[0][2]*z + mInv.m[0][3];
  float yp = mInv.m[1][0]*x + mInv.m[1][1]*y + mInv.m[1][2]*z + mInv.m[1][3];
  float zp = mInv.m[2][0]*x + mInv.m[2][1]*y + mInv.m[2][2]*z + mInv.m[2][3];
  float wp = mInv.m[3][0]*x + mInv.m[3][1]*y + mInv.m[3][2]*z + mInv.m[3][3];

  // Implicitly convert point back to non-homogeneous coordinates
  if (wp == 1.f)
    return Point(xp, yp, zp);
  else
    return Point(xp, yp, zp) * (1/wp);
}

Vector Transform::Invert(const Vector& v) const {
  float x = v.x, y = v.y, z = v.z;
  return Vector(mInv.m[0][0] * x + mInv.m[0][1] * y + mInv.m[0][2] * z,
                mInv.m[1][0] * x + mInv.m[1][1] * y + mInv.m[1][2] * z,
                mInv.m[2][0] * x + mInv.m[2][1] * y + mInv.m[2][2] * z);
}

Point& Transform::ApplyInvert(Point* p) const {
  float x = p->x, y = p->y, z = p->z;

  // Implicitly convert point to homogeneous coordinates
  float xp = mInv.m[0][0]*x + mInv.m[0][1]*y + mInv.m[0][2]*z + mInv.m[0][3];
  float yp = mInv.m[1][0]*x + mInv.m[1][1]*y + mInv.m[1][2]*z + mInv.m[1][3];
  float zp = mInv.m[2][0]*x + mInv.m[2][1]*y + mInv.m[2][2]*z + mInv.m[2][3];
  float wp = mInv.m[3][0]*x + mInv.m[3][1]*y + mInv.m[3][2]*z + mInv.m[3][3];

  // Implicitly convert point back to non-homogeneous coordinates
  if (wp == 1.f) {
    p->x = xp;
    p->y = yp;
    p->z = zp;
  } else {
    float f = 1/wp;
    p->x = xp * f;
    p->y = yp * f;
    p->z = zp * f;
  }

  return *p;
}

Vector& Transform::ApplyInvert(Vector* v) const {
  float x = v->x, y = v->y, z = v->z;
  v->x = mInv.m[0][0] * x + mInv.m[0][1] * y + mInv.m[0][2] * z;
  v->y = mInv.m[1][0] * x + mInv.m[1][1] * y + mInv.m[1][2] * z;
  v->z = mInv.m[2][0] * x + mInv.m[2][1] * y + mInv.m[2][2] * z;
  return *v;
}

Transform Inverse(const Transform& t) {
  return Transform(t.mInv, t.m);
}

Transform Translate(const Vector& delta) {
  Matrix4x4 mat = Matrix4x4(1.f, 0.f, 0.f, delta.x,
                            0.f, 1.f, 0.f, delta.y,
                            0.f, 0.f, 1.f, delta.z,
                            0.f, 0.f, 0.f, 1.0f);
  Matrix4x4 matInv = Matrix4x4(1.f, 0.f, 0.f, -delta.x,
                               0.f, 1.f, 0.f, -delta.y,
                               0.f, 0.f, 1.f, -delta.z,
                               0.f, 0.f, 0.f, 1.0f);
  return Transform(mat, matInv);
}

Transform RotateX(float angle) {
  float c = cos(angle);
  float s = sin(angle);

  Matrix4x4 mat = Matrix4x4(1.f, 0.f, 0.f, 0.f,
                            0.f, c, -s, 0.f,
                            0.f, s, c, 0.f,
                            0.f, 0.f, 0.f, 1.f);
  Matrix4x4 matInv = Matrix4x4(1.f, 0.f, 0.f, 0.f,
                               0.f,   c,   s, 0.f,
                               0.f,  -s,   c, 0.f,
                               0.f, 0.f, 0.f, 1.f);
  return Transform(mat, matInv);
}

Transform RotateY(float angle) {
  float c = cos(angle);
  float s = sin(angle);

  Matrix4x4 mat = Matrix4x4(c, 0.f, s, 0.f,
                            0.f, 1.f, 0.f, 0.f,
                            -s, 0.f, c, 0.f,
                            0.f, 0.f, 0.f, 1.f);
  Matrix4x4 matInv = Matrix4x4(c, 0.f, -s, 0.f,
                               0.f, 1.f, 0.f, 0.f,
                               s, 0.f, c, 0.f,
                               0.f, 0.f, 0.f, 1.f);
  return Transform(mat, matInv);
}

Transform RotateZ(float angle) {
  float c = cos(angle);
  float s = sin(angle);

  Matrix4x4 mat = Matrix4x4(c, -s, 0.f, 0.f,
                            s,  c, 0.f, 0.f,
                            0.f, 0.f, 1.f, 0.f,
                            0.f, 0.f, 0.f, 1.f);
  Matrix4x4 matInv = Matrix4x4(c,  s, 0.f, 0.f,
                               -s, c, 0.f, 0.f,
                               0.f, 0.f, 1.f, 0.f,
                               0.f, 0.f, 0.f, 1.f);
  return Transform(mat, matInv);
}

/*
Transform Rotate(float angle, const Vector& axis) {

}

Transform Scale(float x, float y, float z) {

}
*/

}  // namespace ishi
