#pragma once

#ifndef _H_MATH_VECTOR2D_
#define _H_MATH_VECTOR2D_

#include <assert.h>
namespace math {
typedef struct Vector2D {
 public:
  Vector2D(void);
  Vector2D(float xi, float yi);

  float Magnitude(void) const;
  void Normalize(void);
  Vector2D Normalized(void) const;
  void Reverse(void);

  float& operator[](int i) {
    assert(i >= 0 && i < 3);
    return as_array_[i];
  }

  Vector2D& operator+=(const Vector2D& u);
  Vector2D& operator-=(const Vector2D& u);
  Vector2D& operator*=(const Vector2D& u);
  Vector2D& operator/=(const Vector2D& u);

  Vector2D operator-(void);

 public:
  static Vector2D Zero;

 public:
  union {
    struct {
      float x_;
      float y_;
    };

    float as_array_[2];
  };

} Vector2D;

Vector2D operator+(const Vector2D& u, const Vector2D& v);
Vector2D operator-(const Vector2D& u, const Vector2D& v);

/*
 * 2d vector cross product
 * The cross product of 2D vectors results in a 3D vector with only a z
 * component. This function returns the magnitude of the z value.
 */
float operator^(const Vector2D& u, const Vector2D& v);

// dot product
float operator*(const Vector2D& u, const Vector2D& v);
float Dot(const Vector2D& u, const Vector2D& v);

/*
 * scalar multiplication
 */
Vector2D operator*(float s, const Vector2D& u);
Vector2D operator*(const Vector2D& u, float s);

/*
 * scalar devision
 */
Vector2D operator/(const Vector2D& u, float s);

/*
 * compare operators
 */
bool operator==(const Vector2D& u, const Vector2D& v);
bool operator!=(const Vector2D& u, const Vector2D& v);

float Magnitude(const Vector2D& v);
float MagnitudeSq(const Vector2D& v);

Vector2D Normalized(const Vector2D& v);

float Angle(const Vector2D& u, const Vector2D& v);

Vector2D Project(const Vector2D& len, const Vector2D& dir);
Vector2D Perpendicular(const Vector2D& len, const Vector2D& dir);
/*
 * triple scalar product
 * s = u dot (v cross w)
 */
Vector2D TripleScalarProduct(const Vector2D& u, const Vector2D& v,
                             const Vector2D& w);
}  // namespace math

#endif  //_H_MATH_VECTOR2D_