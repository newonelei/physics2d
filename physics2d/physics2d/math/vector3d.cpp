#include "Vector3D.h"
#include "math/float_utils.h"

namespace math {
Vector3D::Vector3D(void) : x_(0), y_(0), z_(0) {}

inline Vector3D::Vector3D(float xi, float yi, float zi)
    : x_(xi), y_(yi), z_(zi) {}

inline float Vector3D::Magnitude(void) const {
  return sqrtf(Dot(*this, *this));
}

inline void Vector3D::Normalize(void) {
  constexpr float tol = 0.00001f;
  float m = Magnitude();
  if (m < tol) {
    // if magnitude is too small, we need to ignore it
    // otherwise the x_ / m will be super big so that float cannot contains that
    // number
    m = 1;
  }
  x_ /= m;
  y_ /= m;
  z_ /= m;

  if (fabs(x_) < tol) x_ = 0.0f;
  if (fabs(y_) < tol) y_ = 0.0f;
  if (fabs(z_) < tol) z_ = 0.0f;
}

Vector3D Vector3D::Normalized(void) const {
  Vector3D vec = *this;
  vec.Normalize();
  return vec;
}

inline void Vector3D::Reverse(void) {
  x_ = -x_;
  y_ = -y_;
  z_ = -z_;
}

inline Vector3D& Vector3D::operator+=(const Vector3D& u) {
  x_ += u.x_;
  y_ += u.y_;
  z_ += u.z_;
  return *this;
}

inline Vector3D& Vector3D::operator-=(const Vector3D& u) {
  x_ -= u.x_;
  y_ -= u.y_;
  z_ -= u.z_;
  return *this;
}

inline Vector3D& Vector3D::operator*=(const Vector3D& u) {
  x_ *= u.x_;
  y_ *= u.y_;
  z_ *= u.z_;
  return *this;
}

inline Vector3D& Vector3D::operator/=(const Vector3D& u) {
  x_ /= u.x_;
  y_ /= u.y_;
  z_ /= u.z_;
  return *this;
}

inline Vector3D Vector3D::operator-(void) { return Vector3D(-x_, -y_, -z_); }

inline Vector3D operator+(const Vector3D& u, const Vector3D& v) {
  return Vector3D(u.x_ + v.x_, u.y_ + v.y_, u.z_ + v.z_);
}

inline Vector3D operator-(const Vector3D& u, const Vector3D& v) {
  return Vector3D(u.x_ - v.x_, u.y_ - v.y_, u.z_ - v.z_);
}

/*
 * vector cross product
 */
inline Vector3D operator^(const Vector3D& u, const Vector3D& v) {
  return Vector3D(u.y_ * v.z_ - u.z_ * v.y_, u.z_ * v.x_ - u.x_ * v.z_,
                  u.x_ * v.y_ - u.y_ * v.x_);
}

inline Vector3D Cross(const Vector3D& u, const Vector3D& v) {
  Vector3D result;
  result.x_ = u.y_ * v.z_ - u.z_ * v.y_;
  result.y_ = u.z_ * v.x_ - u.x_ * v.z_;
  result.z_ = u.x_ * v.y_ - u.y_ * v.x_;
  return result;
}

// dot product
inline float operator*(const Vector3D& u, const Vector3D& v) {
  return static_cast<float>(u.x_ * v.x_ + u.y_ * v.y_ + u.z_ * v.z_);
}

inline float Dot(const Vector3D& u, const Vector3D& v) { return u * v; }

/*
 * scalar multiplication
 */
inline Vector3D operator*(float s, const Vector3D& u) {
  return Vector3D(s * u.x_, s * u.y_, s * u.z_);
}

inline Vector3D operator*(const Vector3D& u, float s) {
  return Vector3D(s * u.x_, s * u.y_, s * u.z_);
}

/*
 * scalar devision
 */
inline Vector3D operator/(const Vector3D& u, float s) {
  return Vector3D(u.x_ / s, u.y_ / s, u.z_ / s);
}

bool operator==(const Vector3D& u, const Vector3D& v) {
  return CMP(u.x_, v.x_) && CMP(u.y_, v.y_) && CMP(u.z_, v.z_);
}

bool operator!=(const Vector3D& u, const Vector3D& v) { return !(u == v); }

float Magnitude(const Vector3D& v) { return sqrtf(v * v); }
float MagnitudeSq(const Vector3D& v) { return v * v; }

Vector3D Normalized(const Vector3D& v) { return v.Normalized(); }

inline float Angle(const Vector3D& u, const Vector3D& v) {
  float m = sqrtf(MagnitudeSq(u) * MagnitudeSq(v));
  return acos(Dot(u, v) / m);
}

/*
 * triple scalar product
 * s = u dot (v cross w)
 */
inline float TripleScalarProduct(const Vector3D& u, const Vector3D& v,
                                 const Vector3D& w) {
  return u * (v ^ w);
}
}  // namespace math