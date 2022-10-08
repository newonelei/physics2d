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

  // default constructor for identity matrix
  inline Matrix3D() {
    _11 = _22 = _33 = 1.0f;
    _12 = _13 = 0.0f;
    _21 = _23 = 0.0f;
    _31 = _32 = 0.0f;
  }

  inline Matrix3D(float f11, float f12, float f13, float f21, float f22,
                  float f23, float f31, float f32, float f33)
      : _11{f11},
        _12{f12},
        _13{f13},
        _21{f21},
        _22{f22},
        _23{f23},
        _31{f31},
        _32{f32},
        _33{f33} {}

  // return row vector
  inline float* operator[](int i) {
    // max 3 rows
    assert(i >= 0 && i <= 2);
    return &as_array_[i * 3];
  }

  // return row const vector
  inline const float* operator[](int i) const {
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

float Determinant(const Matrix3D& mat);

Matrix3D Minor(const Matrix3D& mat);

Matrix3D Cofactor(const Matrix3D& mat);
}  // namespace math

#endif  // _H_MATRIX_3D_