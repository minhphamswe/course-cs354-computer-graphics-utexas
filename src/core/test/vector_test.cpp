#include <core/vector.h>
#include <UnitTest++/UnitTest++.h>

using namespace ishi;

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

TEST(VectorUnaryMinus) {
  Vector v;

  v = Vector(1, 0, 0);
  CHECK_EQUAL( -1, (-v).x);
  CHECK_EQUAL(0, (-v).y);
  CHECK_EQUAL(0, (-v).z);

  v = -Vector(1, 2, 3);
  CHECK_EQUAL(-1, v.x);
  CHECK_EQUAL(-2, v.y);
  CHECK_EQUAL(-3, v.z);
}

TEST(VectorEquality) {
  Vector v;

  v = Vector(1, 0, 0);
  CHECK(v == v);
  CHECK(v == Vector(1, 0, 0));
  CHECK(Vector(1, 0, 0) == Vector(1, 0, 0));

  v = Vector(4, 5, 6);
  CHECK(v == v);
  CHECK(v == Vector(4, 5, 6));
  CHECK(Vector(4, 5, 6) == Vector(4, 5, 6));
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

TEST(VectorMultiplication) {
  Vector v;

  v = Vector(1, 2, 3) * 5;
  CHECK(v == Vector(5, 10, 15));

  v = 5 * Vector(1, 2, 3);
  CHECK(v == Vector(5, 10, 15));

  v = Vector(1, 2, 3);
  v *= 5;
  CHECK(v == Vector(5, 10, 15));
}

TEST(VectorVectorAddition) {
  Vector v1, v2, v;

  v1 = Vector(1, 2, 3);
  v2 = Vector(4, 5, 6);

  // Check addition identity
  v = v1 + Vector(0, 0, 0);
  CHECK(v == Vector(1, 2, 3));

  v = v2 + Vector(0, 0, 0);
  CHECK(v == Vector(4, 5, 6));

  // Check result of addition
  v = v1 + v2;
  CHECK(v == Vector(5, 7, 9));

  // Check addition is commutative
  CHECK((v1 + v2) == (v2 + v1));
}

TEST(VectorVectorIncrement) {
  Vector v1, v2, v;

  v1 = Vector(1, 2, 3);
  v2 = Vector(4, 5, 6);

  // Check result of increment
  v = v1;
  v += v2;
  CHECK(v == Vector(5, 7, 9));

  // Check result of increment
  v = v2;
  v += v1;
  CHECK(v == Vector(5, 7, 9));
}

TEST(VectorVectorSubtration) {
  Vector v1, v2, v;

  v1 = Vector(1, 2, 3);
  v2 = Vector(4, 5, 6);

  // Check subtraction identity
  v = v1 - Vector(0, 0, 0);
  CHECK(v == Vector(1, 2, 3));

  v = v2 - Vector(0, 0, 0);
  CHECK(v == Vector(4, 5, 6));

  // Check result of subtraction
  v = v2 - v1;
  CHECK(v == Vector(3, 3, 3));

  v = v1 - v2;
  CHECK(v == Vector(-3, -3, -3));

  // Check result of decrement
  v -= v2;
  CHECK(v == Vector(-7, -8, -9));

  // Check addition is anticommutative
  CHECK((v1 - v2) == -(v2 - v1));
}

TEST(DotProduct) {
  Vector v1, v2;

  // Check "2D" Vector
  v1 = Vector(1, 0);
  v2 = Vector(0, 5);
  CHECK_EQUAL(Dot(v1, v2), 0);  // orthogonal
  CHECK_EQUAL(Dot(v1, v2), Dot(v2, v1));  // commutative

  v1 = Vector(1, 2);
  v2 = Vector(4, 5);
  CHECK_EQUAL(Dot(v1, v2), 14);
  CHECK_EQUAL(Dot(v1, v2), Dot(v2, v1));  // commutative

  // Check "3D" Vector
  v1 = Vector(1, 0, 0);
  v2 = Vector(0, 5, 0);
  CHECK_EQUAL(Dot(v1, v2), 0);  // orthogonal
  CHECK_EQUAL(Dot(v1, v2), Dot(v2, v1));  // commutative

  v1 = Vector(0, 0, 3);
  v2 = Vector(0, 5, 0);
  CHECK_EQUAL(Dot(v1, v2), 0);  // orthogonal
  CHECK_EQUAL(Dot(v1, v2), Dot(v2, v1));  // commutative

  v1 = Vector(1, 0, 0);
  v2 = Vector(0, 0, 6);
  CHECK_EQUAL(Dot(v1, v2), 0);  // orthogonal
  CHECK_EQUAL(Dot(v1, v2), Dot(v2, v1));  // commutative

  v1 = Vector(1, 2, 3);
  v2 = Vector(4, 5, 6);
  CHECK_EQUAL(Dot(v1, v2), 32);
  CHECK_EQUAL(Dot(v1, v2), Dot(v2, v1));  // commutative
}

TEST(CrossProduct) {
  Vector v1, v2;

  // Check (i x j == k), (j x i == -k)
  v1 = Vector(1, 0, 0);
  v2 = Vector(0, 1, 0);
  CHECK(Cross(v1, v2) == Vector(0, 0, 1));
  CHECK(Cross(v1, v2) == -Cross(v2, v1));

  // Check (j x k == i), (k x j == -i)
  v1 = Vector(0, 1, 0);
  v2 = Vector(0, 0, 1);
  CHECK(Cross(v1, v2) == Vector(1, 0, 0));
  CHECK(Cross(v1, v2) == -Cross(v2, v1));

  // Check (k x i == j), (i x k == -j)
  v1 = Vector(0, 0, 1);
  v2 = Vector(1, 0, 0);
  CHECK(Cross(v1, v2) == Vector(0, 1, 0));
  CHECK(Cross(v1, v2) == -Cross(v2, v1));

  v1 = Vector(1, 2, 3);
  v2 = Vector(4, 5, 6);
  CHECK(Cross(v1, v2) == Vector(-3, 6, -3));
  CHECK(Cross(v1, v2) == -Cross(v2, v1));
}
