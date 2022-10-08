#include "matrices.h"
#include <cmath>

namespace math {
void Transpose(const float* srcMat, float* dstMat, int srcRows, int srcCols) {
  for (int i = 0; i < srcRows * srcCols; ++i) {
    int row = i / srcRows;
    int col = i % srcRows;
    dstMat[i] = srcMat[srcCols * col +
                       row];  // transposed element index on i([srcCols * row +
                              // col]) is j([srcCols * col + row])
  }
}

bool Multiply(float* out, const float* mat_a, int a_rows, int a_cols,
              const float* mat_b, int b_rows, int b_cols) {
  if (a_cols != b_rows) {
    return false;
  }

  for (int i = 0; i < a_rows; ++i) {
    for (int j = 0; j < a_cols; ++j) {
      int mat_out_idx = b_cols * i + j;
      out[mat_out_idx] = 0.0f;
      for (int k = 0; k < b_rows; ++k) {
        int mat_a_index = a_cols * i + k;
        int mat_b_index = b_cols * k + j;
        out[mat_out_idx] += mat_a[mat_a_index] * mat_b[mat_b_index];
      }
    }
  }

  return true;
}

// explicit Cut template instantiation
template Matrix2D Cut<Matrix2D, Matrix3D, 3, 3>(const Matrix3D&, int, int);

template Matrix3D Cut<Matrix3D, Matrix4D, 4, 4>(const Matrix4D&, int, int);

void Cofactor(float* out, const float* minor, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      int target = j * cols + i;       // target index
      int source = target;             // source index
	  float sign = (i + j) % 2 == 0 ? 1.0f : -1.0f;// pow(-1.0f, i + j);  // -1 or 1
      out[target] = minor[source] * sign;
    }
  }
}
}  // namespace math
