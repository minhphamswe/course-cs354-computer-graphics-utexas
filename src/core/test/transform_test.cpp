#include <core/transform.h>
#include <core/vector.h>
#include <core/point.h>
#include <UnitTest++/UnitTest++.h>
#include <cstdio>

using namespace ishi;

/// Verify that a concatentated transform is equivalent to applying
/// transforms in sequential order from right to left.
/// Test is only done concatentation of different types. Concatenations of
/// same-type transformations have their own tests.
TEST(TransformConcatenationOrder) {
  Point p;
  Vector delta;
  float angle;
  float range = 2.f;
  float step = 0.1f;

  for (float i = -range; i < range; i+=step) {
    for (float j = -range; j < range; j+=step) {
      for (float k = -range; k < range; k+=step) {
        // set the variables
        p = Point(i, j, k);
        angle = i;
        delta = Vector(k, i, j);

        // test rotation and then translation
        CHECK((Translate(delta) * RotateX(angle))(p) ==
              (Translate(delta)(RotateX(angle)(p))));

        CHECK((Translate(delta) * RotateY(angle))(p) ==
              (Translate(delta)(RotateY(angle)(p))));

        CHECK((Translate(delta) * RotateZ(angle))(p) ==
              (Translate(delta)(RotateZ(angle)(p))));

        // test translation and then rotation
        CHECK((RotateX(angle) * Translate(delta))(p) ==
              (RotateX(angle)(Translate(delta)(p))));

        CHECK((RotateY(angle) * Translate(delta))(p) ==
              (RotateY(angle)(Translate(delta)(p))));

        CHECK((RotateZ(angle) * Translate(delta))(p) ==
              (RotateZ(angle)(Translate(delta)(p))));
      }
    }
  }
}

/// Verify that destructive (in-place) and non-destructive versions of
/// transformations give the same result.

/// Verify that inverses applied in consecutive orders cancel out
TEST(InversesCancel) {
  Point p;
  Vector delta;
  float angle;
  float range = 2.f;
  float step = 0.1f;

  for (float i = -range; i < range; i+=step) {
    for (float j = -range; j < range; j+=step) {
      for (float k = -range; k < range; k+=step) {
        p = Point(i, j, k);
        angle = i;
        delta = Vector(k, i, j);

        // test rotation
        CHECK((RotateX(angle) * Inverse(RotateX(angle)))(p) == p);
        CHECK((RotateY(angle) * Inverse(RotateY(angle)))(p) == p);
        CHECK((RotateZ(angle) * Inverse(RotateZ(angle)))(p) == p);

        // test translation
        CHECK((Translate(delta) * Inverse(Translate(delta)))(p) == p);
      }
    }
  }
}

/// Verify that rotation around axis gives the same result if the direction
/// of the axis is the same (regardless of scale)
TEST(RotateArbitraryAxisScaleInvariant) {
  Point p = Point(1, 2, 3);
  Vector v = Vector(4, 5, 6);
  float angle = 0.7;

  CHECK(Rotate(angle, Vector(1.2, 0.f, 0.f))(p) == Rotate(angle, Vector(1.f, 0.f, 0.f))(p));
  CHECK(Rotate(angle, Vector(0.f, 3.4, 0.f))(p) == Rotate(angle, Vector(0.f, 1.f, 0.f))(p));
  CHECK(Rotate(angle, Vector(0.f, 0.f, 5.6))(p) == Rotate(angle, Vector(0.f, 0.f, 1.f))(p));

  CHECK(Rotate(angle, Vector(1.2, 0.f, 0.f))(v) == Rotate(angle, Vector(1.f, 0.f, 0.f))(v));
  CHECK(Rotate(angle, Vector(0.f, 3.4, 0.f))(v) == Rotate(angle, Vector(0.f, 1.f, 0.f))(v));
  CHECK(Rotate(angle, Vector(0.f, 0.f, 5.6))(v) == Rotate(angle, Vector(0.f, 0.f, 1.f))(v));
}

/// Verify that rotation around an arbitrary axis gives the same result
/// as rotation around X, Y, and Z if the axis of rotation is parallel to the
/// X, Y, and Z, respectively.
TEST(RotateArbitraryAxisCoincidesRotatePrincipalAxis) {
  Point p = Point(1, 2, 3);
  Vector v = Vector(4, 5, 6);
  float angle = 0.7;

  CHECK(Rotate(angle, Vector(1.2, 0.f, 0.f))(p) == RotateX(angle)(p));
  CHECK(Rotate(angle, Vector(0.f, 3.4, 0.f))(p) == RotateY(angle)(p));
  CHECK(Rotate(angle, Vector(0.f, 0.f, 5.6))(p) == RotateZ(angle)(p));

  CHECK(Rotate(angle, Vector(1.2, 0.f, 0.f))(v) == RotateX(angle)(v));
  CHECK(Rotate(angle, Vector(0.f, 3.4, 0.f))(v) == RotateY(angle)(v));
  CHECK(Rotate(angle, Vector(0.f, 0.f, 5.6))(v) == RotateZ(angle)(v));
}