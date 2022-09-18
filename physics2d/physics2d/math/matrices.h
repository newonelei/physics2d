#pragma once

#include "matrix2d.h"
#include "matrix3d.h"
#include "matrix4d.h"

namespace math {
void Transpose(const float* srcMat, float* dstMat, int srcRows, int srcCols);
}