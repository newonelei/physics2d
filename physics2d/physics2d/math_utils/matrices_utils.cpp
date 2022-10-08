#include "matrices_utils.h"

namespace math_utils
{
template ostream& operator<<<Matrix2D, 2, 2>(ostream& os, const Matrix2D& mat);
template ostream& operator<<<Matrix3D, 3, 3>(ostream& os, const Matrix3D& mat);
template ostream& operator<<<Matrix4D, 4, 4>(ostream& os, const Matrix4D& mat);

template string ToString<Matrix2D, 2, 2>(const Matrix2D& mat);
template string ToString<Matrix3D, 3, 3>(const Matrix3D& mat);
template string ToString<Matrix4D, 4, 4>(const Matrix4D& mat);
}
