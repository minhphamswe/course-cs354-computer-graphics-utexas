#include <core/matrix.h>
#include <UnitTest++/UnitTest++.h>

TEST(Matrix4x4DefaultConstructor) {
  Matrix4x4 mat;

  mat = Matrix4x4();
  CHECK_EQUAL(1, mat.m[0][0]);
  CHECK_EQUAL(0, mat.m[0][1]);
  CHECK_EQUAL(0, mat.m[0][2]);
  CHECK_EQUAL(0, mat.m[0][3]);

  CHECK_EQUAL(0, mat.m[1][0]);
  CHECK_EQUAL(1, mat.m[1][1]);
  CHECK_EQUAL(0, mat.m[1][2]);
  CHECK_EQUAL(0, mat.m[1][3]);

  CHECK_EQUAL(0, mat.m[2][0]);
  CHECK_EQUAL(0, mat.m[2][1]);
  CHECK_EQUAL(1, mat.m[2][2]);
  CHECK_EQUAL(0, mat.m[2][3]);

  CHECK_EQUAL(0, mat.m[3][0]);
  CHECK_EQUAL(0, mat.m[3][1]);
  CHECK_EQUAL(0, mat.m[3][2]);
  CHECK_EQUAL(1, mat.m[3][3]);
}

TEST(Matrix4x4ArrayConstructor) {
  Matrix4x4 mat;
  float m[4][4] = {
    {1.f, 2.f, 3.f, 4.f},
    {5.f, 6.f, 7.f, 8.f},
    {1.5, 2.6, 3.7, 4.8},
    {5.1, 6.2, 7.3, 8.4}
  };

  mat = Matrix4x4(m);
  CHECK_ARRAY2D_CLOSE(m, mat.m, 4, 4, 0.00);
}

TEST(Matrix4x4FloatListConstructor) {
  Matrix4x4 mat;
  float m[4][4] = {
    {1.f, 2.f, 3.f, 4.f},
    {5.f, 6.f, 7.f, 8.f},
    {1.5, 2.6, 3.7, 4.8},
    {5.1, 6.2, 7.3, 8.4}
  };

  mat = Matrix4x4(1.f, 2.f, 3.f, 4.f,
                  5.f, 6.f, 7.f, 8.f,
                  1.5, 2.6, 3.7, 4.8,
                  5.1, 6.2, 7.3, 8.4);
  CHECK_ARRAY2D_CLOSE(m, mat.m, 4, 4, 0.00);
}

TEST(Matrix4x4EqualityOperator) {
  Matrix4x4 m1, m2;

  float m[4][4] = {
    {1.f, 2.f, 3.f, 4.f},
    {5.f, 6.f, 7.f, 8.f},
    {1.5, 2.6, 3.7, 4.8},
    {5.1, 6.2, 7.3, 8.4}
  };

  m1 = Matrix4x4(m);
  m2 = Matrix4x4(1.f, 2.f, 3.f, 4.f,
                 5.f, 6.f, 7.f, 8.f,
                 1.5, 2.6, 3.7, 4.8,
                 5.1, 6.2, 7.3, 8.4);
  
  CHECK(Matrix4x4() == Matrix4x4());
  CHECK(m1 == m2);
}