#pragma once

#ifndef _H_MATRIX_2D_
#define _H_MATRIX_2D_

#include <assert.h>

namespace math {
typedef struct Matrix2D {
  union {
    struct {
      float _11, _12, _21, _22;
    };

    float as_array_[4];
  };

  // return row vector
  inline float* operator[](int i) {
    // max 2 rows
    assert(i >= 0 && i <= 1);
    return &as_array_[i * 2];
  }
} Matrix2D;

// transpose
Matrix2D Transpose(const Matrix2D& matrix);

// scalar multiplication
Matrix2D operator*(const Matrix2D& mat, float scalar);

// matrix multiply
Matrix2D operator*(const Matrix2D& mat_a, const Matrix2D& mat_b);
}  // namespace math
#endif  // _H_MATRIX_2D_