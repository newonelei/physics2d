#include "matrix2d.h"
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
}  // namespace math