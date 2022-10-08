#pragma once

#include "matrix2d.h"
#include "matrix3d.h"
#include "matrix4d.h"

namespace math {
void Transpose(const float* srcMat, float* dstMat, int srcRows, int srcCols);

bool Multiply(float* out, const float* mat_a, int a_rows, int a_cols,
              const float* mat_b, int b_rows, int b_cols);

template <typename MatCutT, typename MatSrcT, int ROW, int COL>
MatCutT Cut(const MatSrcT& mat, int row, int col) {
  MatCutT result;

  int index = 0;
  for (int i = 0; i < ROW; ++i) {
    for (int j = 0; j < COL; ++j) {
      if (i == row || j == col) continue;

	  int target = index++;
	  int source = i * COL + j;
      result.as_array_[target] = mat.as_array_[source];
    }
  }

  return result;
}

void Cofactor(float* out, const float* minor, int rows, int cols);
}  // namespace math