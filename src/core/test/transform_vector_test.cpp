#include <core/transform.h>
#include <core/vector.h>
#include <core/point.h>
#include <UnitTest++/UnitTest++.h>

using namespace ishi;

/// Verify identity transform does not affect either point or vector
TEST(IdentityOnPointAndVector) {
  Vector v = Vector(5.1, 6.2, 7.3);
  Transform t = Transform();
  CHECK(v == t(v));
}

/// Verify inverse identity transform does not affect either point or vector
TEST(InverseIdentityOnPointAndVector) {
  Vector v = Vector(5.1, 6.2, 7.3);
  Transform t = Inverse(Transform());
  CHECK(v == t(v));
}

/// Verify translation does not affect vector
TEST(TranslationOnVector) {
  Vector v, d;
  Transform t;

  v = Vector(1, 2, 3);

  // Translate in X direction
  d = Vector(5.1, 0.f, 0.f);
  t = Translate(d);
  CHECK(t(v) == v);

  // Translate in Y direction
  d = Vector(0.f, 6.2, 0.f);
  t = Translate(d);
  CHECK(t(v) == v);

  // Translate in Z direction
  d = Vector(0.f, 0.f, 7.3);
  t = Translate(d);
  CHECK(t(v) == v);

  // Translate in all 3 directions
  d = Vector(5.1, 6.2, 7.3);
  t = Translate(d);
  CHECK(t(v) == v);
}

/// Verify inverse translation does not affect vector
TEST(InverseTranslationOnVector) {
  Vector v, d;
  Transform t;

  v = Vector(1, 2, 3);

  // Translate in X direction
  d = Vector(5.1, 0.f, 0.f);
  t = Inverse(Translate(d));
  CHECK(t(v) == v);

  // Translate in Y direction
  d = Vector(0.f, 6.2, 0.f);
  t = Inverse(Translate(d));
  CHECK(t(v) == v);

  // Translate in Z direction
  d = Vector(0.f, 0.f, 7.3);
  t = Inverse(Translate(d));
  CHECK(t(v) == v);

  // Translate in all 3 directions
  d = Vector(5.1, 6.2, 7.3);
  t = Inverse(Translate(d));
  CHECK(t(v) == v);
}

TEST(RotationXOnVector) {
  Vector v = Vector(1, 2, 3);
}

TEST(ApplyInverseRotationX) {
  
}

TEST(ApplyRotationY) {
  
}

TEST(ApplyInverseRotationY) {
  
}

TEST(ApplyRotationZ) {
  
}

TEST(ApplyInverseRotationZ) {
  
}

TEST(ApplyScale) {
  
}

TEST(ApplyInverseScale) {
  
}

