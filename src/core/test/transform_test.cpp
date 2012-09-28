#include <core/transform.h>
#include <core/vector.h>
#include <core/point.h>
#include <UnitTest++/UnitTest++.h>

TEST(ApplyIdentityTransform) {
  Vector v = Vector(5.1, 6.2, 7.3);
  Transform t = Transform();
  CHECK(v == t(v));

  Point p = Point(5.1, 6.2, 7.3);
  CHECK(p == t(p));
}

TEST(ApplyInverseIdentityTransform) {
  Vector v = Vector(5.1, 6.2, 7.3);
  Transform t = Inverse(Transform());
  CHECK(v == t(v));

  Point p = Point(5.1, 6.2, 7.3);
  CHECK(p == t(p));
}

TEST(ApplyTranslationToVector) {
  Vector v, d;
  Transform t;

  v = Vector(1, 2, 3);

  // Translate in X direction
  d = Vector(5.1, 0.f, 0.f);
  t = Translate(d);
  CHECK(t(v) == v+d);

  // Translate in Y direction
  d = Vector(0.f, 6.2, 0.f);
  t = Translate(d);
  CHECK(t(v) == v+d);

  // Translate in Z direction
  d = Vector(0.f, 0.f, 7.3);
  t = Translate(d);
  CHECK(t(v) == v+d);

  // Translate in all 3 directions
  d = Vector(5.1, 6.2, 7.3);
  t = Translate(d);
  CHECK(t(v) == v+d);
}

TEST(ApplyInverseTranslationToVector) {
  Vector v, d;
  Transform t;

  v = Vector(1, 2, 3);

  // Translate in X direction
  d = Vector(5.1, 0.f, 0.f);
  t = Translate(d);
  CHECK(t(v) == v-d);

  // Translate in Y direction
  d = Vector(0.f, 6.2, 0.f);
  t = Translate(d);
  CHECK(t(v) == v-d);

  // Translate in Z direction
  d = Vector(0.f, 0.f, 7.3);
  t = Translate(d);
  CHECK(t(v) == v-d);

  // Translate in all 3 directions
  d = Vector(5.1, 6.2, 7.3);
  t = Translate(d);
  CHECK(t(v) == v-d);
}

TEST(ApplyRotationX) {
  
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

