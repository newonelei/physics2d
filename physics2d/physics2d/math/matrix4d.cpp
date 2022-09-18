#include "matrix4d.h"
#include "matrices.h"
namespace math {
Matrix4D Transpose(const Matrix4D& matrix) {
  Matrix4D result;
  Transpose(matrix.as_array_, result.as_array_, 4, 4);
  return result;
}
}  // namespace math