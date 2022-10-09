#include "matrix3d.h"
#include "matrices.h"
#include "float_utils.h"
namespace math {
Matrix3D Transpose(const Matrix3D& matrix) {
  Matrix3D result;
  Transpose(matrix.as_array_, result.as_array_, 3, 3);
  return result;
}

Matrix3D operator*(const Matrix3D& mat, float scalar) {
  Matrix3D result;
  for (int i = 0; i < 9; ++i) {
    result.as_array_[i] = mat.as_array_[i] * scalar;
  }
  return result;
}
Matrix3D operator*(const Matrix3D& mat_a, const Matrix3D& mat_b) {
  Matrix3D result;
  Multiply(result.as_array_, mat_a.as_array_, 3, 3, mat_b.as_array_, 3, 3);
  return result;
}

float Determinant(const Matrix3D& mat) {
  float result = 0.0f;

  Matrix3D cofactor = Cofactor(mat);
  for (int j = 0; j < 3; ++j) {
    int index = j;

    // fetch the first 3 elements in mat.as_array_
    result += mat.as_array_[index] * cofactor[0][j];
  }

  return result;
}

// get matrix of minors
Matrix3D Minor(const Matrix3D& mat) {
  Matrix3D result;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      result[i][j] = Determinant(Cut<Matrix2D, Matrix3D, 3, 3>(mat, i, j));
    }
  }
  return result;
}

// get matrix of cofactors
Matrix3D Cofactor(const Matrix3D& mat) {
  Matrix3D result;
  Cofactor(result.as_array_, Minor(mat).as_array_, 3, 3);
  return result;
}

// adjugate of any order matrix is the transpose of cofactor matrix
Matrix3D Adjugate(const Matrix3D& mat) { return Transpose(Cofactor(mat)); }

// inverse of matrix
Matrix3D Inverse(const Matrix3D& mat) {
  float det = Determinant(mat);
  if (CMP(det, 0.0f)) {
    return Matrix3D();
  }

  return Adjugate(mat) * (1.0f / det);
}
}  // namespace math