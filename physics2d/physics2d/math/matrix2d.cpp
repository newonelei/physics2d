#include "matrix2d.h"
#include "float_utils.h"
#include "matrices.h"

namespace math {
Matrix2D Transpose(const Matrix2D& matrix) {
  Matrix2D result;
  Transpose(matrix.as_array_, result.as_array_, 2, 2);
  return result;
}

Matrix2D operator*(const Matrix2D& mat, float scalar) {
  Matrix2D result;
  for (int i = 0; i < 4; ++i) {
    result.as_array_[i] = mat.as_array_[i] * scalar;
  }
  return result;
}

Matrix2D operator*(const Matrix2D& mat_a, const Matrix2D& mat_b) {
  Matrix2D result;
  Multiply(result.as_array_, mat_a.as_array_, 2, 2, mat_b.as_array_, 2, 2);
  return result;
}

float Determinant(const Matrix2D& mat) {
  return mat._11 * mat._22 - mat._12 * mat._21;
}

// get matrix of minors
Matrix2D Minor(const Matrix2D& mat) {
  return Matrix2D(mat._22, mat._21, mat._12, mat._11);
}

// get matrix of cofactors
Matrix2D Cofactor(const Matrix2D& mat) {
  Matrix2D result;
  Cofactor(result.as_array_, Minor(mat).as_array_, 2, 2);
  return result;
}

// adjugate of any order matrix is the transpose of cofactor matrix
Matrix2D Adjugate(const Matrix2D& mat) { return Transpose(Cofactor(mat)); }

// inverse of matrix
Matrix2D Inverse(const Matrix2D& mat) {
  float det = Determinant(mat);
  if (CMP(det, 0.0f)) {
    return Matrix2D();
  }

  return Adjugate(mat) * (1.0f / det);
}
}  // namespace math