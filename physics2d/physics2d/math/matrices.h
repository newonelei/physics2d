#pragma once

#include "matrix2d.h"
#include "matrix3d.h"
#include "matrix4d.h"

namespace math {
void Transpose(const float* srcMat, float* dstMat, int srcRows, int srcCols);

bool Multiply(float* out, const float* mat_a, int a_rows, int a_cols, const float* mat_b, int b_rows, int b_cols);
}