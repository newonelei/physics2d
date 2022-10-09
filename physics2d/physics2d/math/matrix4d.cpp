#include "matrix4d.h"
#include "float_utils.h"
#include "matrices.h"
namespace math {
Matrix4D Transpose(const Matrix4D& matrix) {
  Matrix4D result;
  Transpose(matrix.as_array_, result.as_array_, 4, 4);
  return result;
}

Matrix4D operator*(const Matrix4D& mat, float scalar) {
  Matrix4D result;
  for (int i = 0; i < 16; ++i) {
    result.as_array_[i] = mat.as_array_[i] * scalar;
  }
  return result;
}

Matrix4D operator*(const Matrix4D& mat_a, const Matrix4D& mat_b) {
  Matrix4D result;
  Multiply(result.as_array_, mat_a.as_array_, 4, 4, mat_b.as_array_, 4, 4);
  return result;
}

float Determinant(const Matrix4D& mat) {
  float result = 0.0f;

  Matrix4D cofactor = Cofactor(mat);
  for (int j = 0; j < 4; ++j) {
    result += mat.as_array_[4 * 0 + j] * cofactor[0][j];
  }
  return result;
}

Matrix4D Minor(const Matrix4D& mat) {
  Matrix4D result;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      result[i][j] = Determinant(Cut<Matrix3D, Matrix4D, 4, 4>(mat, i, j));
    }
  }
  return result;
}

Matrix4D Cofactor(const Matrix4D& mat) {
  Matrix4D result;
  Cofactor(result.as_array_, Minor(mat).as_array_, 4, 4);
  return result;
}

// adjugate of any order matrix is the transpose of cofactor matrix
Matrix4D Adjugate(const Matrix4D& mat) { return Transpose(Cofactor(mat)); }

// inverse of matrix
Matrix4D Inverse(const Matrix4D& m) {
  /*
float det = Determinant(mat);
if (CMP(det, 0.0f)) {
return Matrix4D();
}

return Adjugate(mat) * (1.0f / det);
*/
  // The code below is the expanded form of the above equation.
  // This optimization avoids loops and function calls

  float det = m._11 * m._22 * m._33 * m._44 + m._11 * m._23 * m._34 * m._42 +
              m._11 * m._24 * m._32 * m._43 + m._12 * m._21 * m._34 * m._43 +
              m._12 * m._23 * m._31 * m._44 + m._12 * m._24 * m._33 * m._41 +
              m._13 * m._21 * m._32 * m._44 + m._13 * m._22 * m._34 * m._41 +
              m._13 * m._24 * m._31 * m._42 + m._14 * m._21 * m._33 * m._42 +
              m._14 * m._22 * m._31 * m._43 + m._14 * m._23 * m._32 * m._41 -
              m._11 * m._22 * m._34 * m._43 - m._11 * m._23 * m._32 * m._44 -
              m._11 * m._24 * m._33 * m._42 - m._12 * m._21 * m._33 * m._44 -
              m._12 * m._23 * m._34 * m._41 - m._12 * m._24 * m._31 * m._43 -
              m._13 * m._21 * m._34 * m._42 - m._13 * m._22 * m._31 * m._44 -
              m._13 * m._24 * m._32 * m._41 - m._14 * m._21 * m._32 * m._43 -
              m._14 * m._22 * m._33 * m._41 - m._14 * m._23 * m._31 * m._42;

  if (CMP(det, 0.0f)) {
    return Matrix4D();
  }
  float i_det = 1.0f / det;

  Matrix4D result;
  result._11 =
      (m._22 * m._33 * m._44 + m._23 * m._34 * m._42 + m._24 * m._32 * m._43 -
       m._22 * m._34 * m._43 - m._23 * m._32 * m._44 - m._24 * m._33 * m._42) *
      i_det;
  result._12 =
      (m._12 * m._34 * m._43 + m._13 * m._32 * m._44 + m._14 * m._33 * m._42 -
       m._12 * m._33 * m._44 - m._13 * m._34 * m._42 - m._14 * m._32 * m._43) *
      i_det;
  result._13 =
      (m._12 * m._23 * m._44 + m._13 * m._24 * m._42 + m._14 * m._22 * m._43 -
       m._12 * m._24 * m._43 - m._13 * m._22 * m._44 - m._14 * m._23 * m._42) *
      i_det;
  result._14 =
      (m._12 * m._24 * m._33 + m._13 * m._22 * m._34 + m._14 * m._23 * m._32 -
       m._12 * m._23 * m._34 - m._13 * m._24 * m._32 - m._14 * m._22 * m._33) *
      i_det;
  result._21 =
      (m._21 * m._34 * m._43 + m._23 * m._31 * m._44 + m._24 * m._33 * m._41 -
       m._21 * m._33 * m._44 - m._23 * m._34 * m._41 - m._24 * m._31 * m._43) *
      i_det;
  result._22 =
      (m._11 * m._33 * m._44 + m._13 * m._34 * m._41 + m._14 * m._31 * m._43 -
       m._11 * m._34 * m._43 - m._13 * m._31 * m._44 - m._14 * m._33 * m._41) *
      i_det;
  result._23 =
      (m._11 * m._24 * m._43 + m._13 * m._21 * m._44 + m._14 * m._23 * m._41 -
       m._11 * m._23 * m._44 - m._13 * m._24 * m._41 - m._14 * m._21 * m._43) *
      i_det;
  result._24 =
      (m._11 * m._23 * m._34 + m._13 * m._24 * m._31 + m._14 * m._21 * m._33 -
       m._11 * m._24 * m._33 - m._13 * m._21 * m._34 - m._14 * m._23 * m._31) *
      i_det;
  result._31 =
      (m._21 * m._32 * m._44 + m._22 * m._34 * m._41 + m._24 * m._31 * m._42 -
       m._21 * m._34 * m._42 - m._22 * m._31 * m._44 - m._24 * m._32 * m._41) *
      i_det;
  result._32 =
      (m._11 * m._34 * m._42 + m._12 * m._31 * m._44 + m._14 * m._32 * m._41 -
       m._11 * m._32 * m._44 - m._12 * m._34 * m._41 - m._14 * m._31 * m._42) *
      i_det;
  result._33 =
      (m._11 * m._22 * m._44 + m._12 * m._24 * m._41 + m._14 * m._21 * m._42 -
       m._11 * m._24 * m._42 - m._12 * m._21 * m._44 - m._14 * m._22 * m._41) *
      i_det;
  result._34 =
      (m._11 * m._24 * m._32 + m._12 * m._21 * m._34 + m._14 * m._22 * m._31 -
       m._11 * m._22 * m._34 - m._12 * m._24 * m._31 - m._14 * m._21 * m._32) *
      i_det;
  result._41 =
      (m._21 * m._33 * m._42 + m._22 * m._31 * m._43 + m._23 * m._32 * m._41 -
       m._21 * m._32 * m._43 - m._22 * m._33 * m._41 - m._23 * m._31 * m._42) *
      i_det;
  result._42 =
      (m._11 * m._32 * m._43 + m._12 * m._33 * m._41 + m._13 * m._31 * m._42 -
       m._11 * m._33 * m._42 - m._12 * m._31 * m._43 - m._13 * m._32 * m._41) *
      i_det;
  result._43 =
      (m._11 * m._23 * m._42 + m._12 * m._21 * m._43 + m._13 * m._22 * m._41 -
       m._11 * m._22 * m._43 - m._12 * m._23 * m._41 - m._13 * m._21 * m._42) *
      i_det;
  result._44 =
      (m._11 * m._22 * m._33 + m._12 * m._23 * m._31 + m._13 * m._21 * m._32 -
       m._11 * m._23 * m._32 - m._12 * m._21 * m._33 - m._13 * m._22 * m._31) *
      i_det;

#ifdef DO_SANITY_TESTS
#ifndef NO_EXTRAS
  if (result * m != mat4()) {
    std::cout << "ERROR! Expecting matrix x inverse to equal identity!\n";
  }
#endif
#endif

  return result;
}
}  // namespace math