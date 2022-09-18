#pragma once

#ifndef _H_MATRIX_4D_
#define _H_MATRIX_4D_

#include <assert.h>
namespace math {
typedef struct Matrix4D {
  union {
    struct {
      float _11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41,
          _42, _43, _44;
    };

    float as_array_[16];
  };

  // return row vector
  inline float* operator[](int i) {
    // max 4 rows
    assert(i >= 0 && i <= 3);
    return &as_array_[i * 4];
  }
} Matrix4D;

// transpose
Matrix4D Transpose(const Matrix4D& matrix);

// scalar multiplication
Matrix4D operator*(const Matrix4D& mat, float scalar);
}  // namespace math

#endif  // _H_MATRIX_4D_