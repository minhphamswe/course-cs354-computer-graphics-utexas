#include <core/matrix.h>

Matrix4x4::Matrix4x4() {
  m[0][0] = 1.f;
  m[0][1] = 0.f;
  m[0][2] = 0.f;
  m[0][3] = 0.f;

  m[1][0] = 0.f;
  m[1][1] = 1.f;
  m[1][2] = 0.f;
  m[1][3] = 0.f;

  m[2][0] = 0.f;
  m[2][1] = 0.f;
  m[2][2] = 1.f;
  m[2][3] = 0.f;

  m[3][0] = 0.f;
  m[3][1] = 0.f;
  m[3][2] = 0.f;
  m[3][3] = 1.f;
}

Matrix4x4::Matrix4x4(float mat[4][4]) {
  m[0][0] = mat[0][0];
  m[0][1] = mat[0][1];
  m[0][2] = mat[0][2];
  m[0][3] = mat[0][3];

  m[1][0] = mat[1][0];
  m[1][1] = mat[1][1];
  m[1][2] = mat[1][2];
  m[1][3] = mat[1][3];

  m[2][0] = mat[2][0];
  m[2][1] = mat[2][1];
  m[2][2] = mat[2][2];
  m[2][3] = mat[2][3];

  m[3][0] = mat[3][0];
  m[3][1] = mat[3][1];
  m[3][2] = mat[3][2];
  m[3][3] = mat[3][3];
}

Matrix4x4::Matrix4x4(float a00, float a01, float a02, float a03,
                     float a10, float a11, float a12, float a13,
                     float a20, float a21, float a22, float a23,
                     float a30, float a31, float a32, float a33) {
  m[0][0] = a00;
  m[0][1] = a01;
  m[0][2] = a02;
  m[0][3] = a03;

  m[1][0] = a10;
  m[1][1] = a11;
  m[1][2] = a12;
  m[1][3] = a13;

  m[2][0] = a20;
  m[2][1] = a21;
  m[2][2] = a22;
  m[2][3] = a23;

  m[3][0] = a30;
  m[3][1] = a31;
  m[3][2] = a32;
  m[3][3] = a33;
}


bool Matrix4x4::operator==(const Matrix4x4 &mat) const {
  int i, j;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      if (m[i][j] != mat.m[i][j])
        return false;
  return true;
}

bool Matrix4x4::operator!=(const Matrix4x4 &mat) const {
  
}

Matrix4x4 Inverse(const Matrix4x4& m)
{

}

Matrix4x4 Transpose(const Matrix4x4& m)
{

}

Matrix4x4 Mul(const Matrix4x4& m1, const Matrix4x4& m2)
{

}
