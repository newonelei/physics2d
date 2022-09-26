#include "matrix4d.h"
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
}  // namespace math