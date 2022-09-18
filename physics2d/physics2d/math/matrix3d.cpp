#include "matrix3d.h"
#include "matrices.h"
namespace math {
Matrix3D Transpose(const Matrix3D& matrix) {
  Matrix3D result;
  Transpose(matrix.as_array_, result.as_array_, 3, 3);
  return result;
}
}  // namespace math