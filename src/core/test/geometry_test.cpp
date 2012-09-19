#include <core/geometry.h>
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

TEST(VectorConstructor) {
  Vector v;
  // Default constructor returns origin
  v = Vector();
  CHECK_EQUAL(v.x, 0);
  CHECK_EQUAL(v.y, 0);
  CHECK_EQUAL(v.z, 0);

  // Two arg constructor returns point on 0-plane
  for (float fx = -1.0f; fx < 1.0f; fx += 0.1f) {
    for (float fy = -1.0f; fy < 1.0f; fy += 0.1f) {
      v = Vector(fx, fy);
      CHECK_EQUAL(v.x, fx);
      CHECK_EQUAL(v.y, fy);
      CHECK_EQUAL(v.z, 0);
    }
  }

  // Three arg constructor returns point in 3D space
  for (float fx = -1.0f; fx < 1.0f; fx += 0.1f) {
    for (float fy = -1.0f; fy < 1.0f; fy += 0.1f) {
      for (float fz = -1.0f; fz < 1.0f; fz += 0.1f) {
        v = Vector(fx, fy, fz);
        CHECK_EQUAL(v.x, fx);
        CHECK_EQUAL(v.y, fy);
        CHECK_EQUAL(v.z, fz);
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

TEST(VectorIndexAccessor) {
  Vector v;
  v = Vector(5, 6);
  CHECK_EQUAL(v[0], 5);
  CHECK_EQUAL(v[1], 6);
  CHECK_EQUAL(v[2], 0);

  v = Vector(1, 2, 3);
  CHECK_EQUAL(v[0], 1);
  CHECK_EQUAL(v[1], 2);
  CHECK_EQUAL(v[2], 3);
}

TEST(PointVectorAdditionSubtraction) {
  Point p1, p2, p;
  Vector v1, v2, v;

  p1 = Point(1, 2, 3);
  p2 = Point(4, 5, 6);
  v1 = Vector(4, 5, 6);
  v2 = Vector(1, 2, 3);

  p = p1 + v1;
  CHECK_EQUAL(p.x, 5);
  CHECK_EQUAL(p.y, 7);
  CHECK_EQUAL(p.z, 9);

  p = p2 + v2;
  CHECK_EQUAL(p.x, 5);
  CHECK_EQUAL(p.y, 7);
  CHECK_EQUAL(p.z, 9);
}

TEST(VectorMultiplication) {
  Vector v;

  v = Vector(1, 2, 3) * 5;
  CHECK_EQUAL(v.x, 5);
  CHECK_EQUAL(v.y, 10);
  CHECK_EQUAL(v.z, 15);

  v = 5 * Vector(1, 2, 3);
  CHECK_EQUAL(v.x, 5);
  CHECK_EQUAL(v.y, 10);
  CHECK_EQUAL(v.z, 15);

  v = Vector(1, 2, 3);
  v *= 5;
  CHECK_EQUAL(v.x, 5);
  CHECK_EQUAL(v.y, 10);
  CHECK_EQUAL(v.z, 15);
}