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

  // default constructor for identity matrix
  inline Matrix4D() {
    _11 = _22 = _33 = _44 = 1.0f;
    _12 = _13 = _14 = 0.0f;
    _21 = _23 = _24 = 0.0f;
    _31 = _32 = _34 = 0.0f;
    _41 = _42 = _43 = 0.0f;
  }

  inline Matrix4D(float f11, float f12, float f13, float f14, float f21,
                  float f22, float f23, float f24, float f31, float f32,
                  float f33, float f34, float f41, float f42, float f43,
                  float f44)
      : _11{f11},
        _12{f12},
        _13{f13},
        _14{f14},
        _21{f21},
        _22{f22},
        _23{f23},
        _24{f24},
        _31{f31},
        _32{f32},
        _33{f33},
        _34{f34},
        _41{f41},
        _42{f42},
        _43{f43},
        _44{f44} {}

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

// matrix multiply
Matrix4D operator*(const Matrix4D& mat_a, const Matrix4D& mat_b);
}  // namespace math

#endif  // _H_MATRIX_4D_