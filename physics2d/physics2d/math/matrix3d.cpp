#include "matrix3d.h"
#include "matrices.h"
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
}  // namespace math