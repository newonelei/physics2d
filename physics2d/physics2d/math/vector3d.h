#pragma once

#ifndef _H_MATH_VECTOR3D_
#define _H_MATH_VECTOR3D_

namespace math {
typedef struct Vector3D {
 public:
  Vector3D(void);
  Vector3D(float xi, float yi, float zi);

  float Magnitude(void);
  void Normalize(void);
  void Reverse(void);

  Vector3D& operator+=(const Vector3D& u);
  Vector3D& operator-=(const Vector3D& u);
  Vector3D& operator*=(const Vector3D& u);
  Vector3D& operator/=(const Vector3D& u);

  Vector3D operator-(void);

 public:
  union {
    struct {
      float x_;
      float y_;
      float z_;
    };

    float as_array_[3];
  };

} Vector3D;

Vector3D operator+(const Vector3D& u, const Vector3D& v);
Vector3D operator-(const Vector3D& u, const Vector3D& v);

/*
 * vector cross product
 */
Vector3D operator^(const Vector3D& u, const Vector3D& v);

// dot product
float operator*(const Vector3D& u, const Vector3D& v);
float Dot(const Vector3D& u, const Vector3D& v);

/*
 * scalar multiplication
 */
Vector3D operator*(float s, const Vector3D& u);
Vector3D operator*(const Vector3D& u, float s);

/*
 * scalar devision
 */
Vector3D operator/(const Vector3D& u, float s);

/*
 * compare operators
 */
bool operator==(const Vector3D& u, const Vector3D& v);
bool operator!=(const Vector3D& u, const Vector3D& v);

float Magnitude(const Vector3D& v);
float MagnitudeSq(const Vector3D& v);
    /*
 * triple scalar product
 * s = u dot (v cross w)
 */
float TripleScalarProduct(const Vector3D& u, const Vector3D& v,
                                 const Vector3D& w);
}  // namespace math

#endif