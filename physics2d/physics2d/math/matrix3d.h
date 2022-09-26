#pragma once

#ifndef _H_MATRIX_3D_
#define _H_MATRIX_3D_

#include <assert.h>
namespace math {
typedef struct Matrix3D {
  union {
    struct {
      float _11, _12, _13, _21, _22, _23, _31, _32, _33;
    };

    float as_array_[9];
  };

  // return row vector
  inline float* operator[](int i) {
    // max 3 rows
    assert(i >= 0 && i <= 2);
    return &as_array_[i * 3];
  }
} Matrix3D;

// transpose
Matrix3D Transpose(const Matrix3D& matrix);

// scalar multiplication
Matrix3D operator*(const Matrix3D& mat, float scalar);

// matrix multiply
Matrix3D operator*(const Matrix3D& mat_a, const Matrix3D& mat_b);

}  // namespace math

#endif  // _H_MATRIX_3D_