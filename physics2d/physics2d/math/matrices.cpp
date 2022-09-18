#include "matrices.h"

namespace math {
void Transpose(const float* srcMat, float* dstMat, int srcRows,
                      int srcCols) {
  for (int i = 0; i < srcRows * srcCols; ++i) {
    int row = i / srcRows;
    int col = i % srcRows;
    dstMat[i] = srcMat[srcCols * col + row];
  }
}
}  // namespace math
