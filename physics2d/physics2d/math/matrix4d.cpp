#include "matrix4d.h"
#include "matrices.h"
#include "float_utils.h"
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
Matrix4D Inverse(const Matrix4D& mat) {
  float det = Determinant(mat);
  if (CMP(det, 0.0f)) {
    return Matrix4D();
  }

  return Adjugate(mat) * (1.0f / det);
}
}  // namespace math