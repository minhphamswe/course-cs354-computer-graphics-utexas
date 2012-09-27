#include <core/vector.h>
#include <UnitTest++/UnitTest++.h>

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

TEST(VectorVectorAddition) {
  Vector v1, v2, v;

  v1 = Vector(1, 2, 3);
  v2 = Vector(4, 5, 6);

  // Check addition identity
  v = v1 + Vector(0, 0, 0);
  CHECK_EQUAL(v.x, 1);
  CHECK_EQUAL(v.y, 2);
  CHECK_EQUAL(v.z, 3);

  v = v2 + Vector(0, 0, 0);
  CHECK_EQUAL(v.x, 4);
  CHECK_EQUAL(v.y, 5);
  CHECK_EQUAL(v.z, 6);

  // Check result of addition
  v = v1 + v2;
  CHECK_EQUAL(v.x, 5);
  CHECK_EQUAL(v.y, 7);
  CHECK_EQUAL(v.z, 9);

  // Check result of increment
  v += v2;
  CHECK_EQUAL(v.x, 9);
  CHECK_EQUAL(v.y, 12);
  CHECK_EQUAL(v.z, 15);

  // Check addition is commutative
  CHECK_EQUAL((v1+v2).x, (v2+v1).x);
  CHECK_EQUAL((v1+v2).y, (v2+v1).y);
  CHECK_EQUAL((v1+v2).z, (v2+v1).z);
}

TEST(VectorVectorSubtration) {
  Vector v1, v2, v;

  v1 = Vector(1, 2, 3);
  v2 = Vector(4, 5, 6);

  // Check subtraction identity
  v = v1 - Vector(0, 0, 0);
  CHECK_EQUAL(v.x, 1);
  CHECK_EQUAL(v.y, 2);
  CHECK_EQUAL(v.z, 3);

  v = v2 - Vector(0, 0, 0);
  CHECK_EQUAL(v.x, 4);
  CHECK_EQUAL(v.y, 5);
  CHECK_EQUAL(v.z, 6);

  // Check result of subtraction
  v = v2 - v1;
  CHECK_EQUAL(v.x, 3);
  CHECK_EQUAL(v.y, 3);
  CHECK_EQUAL(v.z, 3);

  v = v1 - v2;
  CHECK_EQUAL(v.x, -3);
  CHECK_EQUAL(v.y, -3);
  CHECK_EQUAL(v.z, -3);

  // Check result of decrement
  v -= v2;
  CHECK_EQUAL(v.x, -7);
  CHECK_EQUAL(v.y, -8);
  CHECK_EQUAL(v.z, -9);

  // Check addition is inversely commutative
  CHECK_EQUAL((v1-v2).x, -(v2-v1).x);
  CHECK_EQUAL((v1-v2).y, -(v2-v1).y);
  CHECK_EQUAL((v1-v2).z, -(v2-v1).z);
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
  CHECK(false);
}
