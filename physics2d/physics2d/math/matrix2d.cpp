#include "matrix2d.h"
#include "matrices.h"
namespace math {
Matrix2D Transpose(const Matrix2D& matrix) {
  Matrix2D result;
  Transpose(matrix.as_array_, result.as_array_, 2, 2);
  return result;
}
}  // namespace math