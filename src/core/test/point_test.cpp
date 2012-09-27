#include <core/point.h>
#include <UnitTest++/UnitTest++.h>

TEST(PointConstructors) {
  Point p;
  // Default constructor returns origin
  p = Point();
  CHECK_EQUAL(p.x, 0);
  CHECK_EQUAL(p.y, 0);
  CHECK_EQUAL(p.z, 0);

  // Two arg constructor returns point on 0-plane
  for (float fx = -1.0f; fx < 1.0f; fx += 0.1f) {
    for (float fy = -1.0f; fy < 1.0f; fy += 0.1f) {
      p = Point(fx, fy);
      CHECK_EQUAL(p.x, fx);
      CHECK_EQUAL(p.y, fy);
      CHECK_EQUAL(p.z, 0);
    }
  }

  // Three arg constructor returns point in 3D space
  for (float fx = -1.0f; fx < 1.0f; fx += 0.1f) {
    for (float fy = -1.0f; fy < 1.0f; fy += 0.1f) {
      for (float fz = -1.0f; fz < 1.0f; fz += 0.1f) {
        p = Point(fx, fy, fz);
        CHECK_EQUAL(p.x, fx);
        CHECK_EQUAL(p.y, fy);
        CHECK_EQUAL(p.z, fz);
      }
    }
  }
}


TEST(PointIndexAccessor) {
  Point p;
  p = Point(5, 6);
  CHECK_EQUAL(p[0], 5);
  CHECK_EQUAL(p[1], 6);
  CHECK_EQUAL(p[2], 0);

  p = Point(1, 2, 3);
  CHECK_EQUAL(p[0], 1);
  CHECK_EQUAL(p[1], 2);
  CHECK_EQUAL(p[2], 3);
}


