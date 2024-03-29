#include "vector2d.h"
#include "math/float_utils.h"

namespace math {
Vector2D Vector2D::Zero = Vector2D();

Vector2D::Vector2D(void) : x_(0.0f), y_(0.0f) {}

Vector2D::Vector2D(float xi, float yi) : x_(xi), y_(yi) {}

float Vector2D::Magnitude(void) const { return sqrtf(Dot(*this, *this)); }

void Vector2D::Normalize(void) {
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

  if (fabs(x_) < tol) x_ = 0.0f;
  if (fabs(y_) < tol) y_ = 0.0f;
}

Vector2D Vector2D::Normalized(void) const {
  Vector2D vec = *this;
  vec.Normalize();
  return vec;
}

void Vector2D::Reverse(void) {
  x_ = -x_;
  y_ = -y_;
}

Vector2D& Vector2D::operator+=(const Vector2D& u) {
  x_ += u.x_;
  y_ += u.y_;
  return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& u) {
  x_ -= u.x_;
  y_ -= u.y_;
  return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& u) {
  x_ *= u.x_;
  y_ *= u.y_;
  return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& u) {
  x_ /= u.x_;
  y_ /= u.y_;
  return *this;
}

Vector2D Vector2D::operator-(void) { return Vector2D(-x_, -y_); }

Vector2D operator+(const Vector2D& u, const Vector2D& v) {
  return Vector2D(u.x_ + v.x_, u.y_ + v.y_);
}

Vector2D operator-(const Vector2D& u, const Vector2D& v) {
  return Vector2D(u.x_ - v.x_, u.y_ - v.y_);
}

/*
 * vector cross product
 */
float operator^(const Vector2D& u, const Vector2D& v) {
  return static_cast<float>(u.x_ * v.y_ - u.y_ * v.x_);
}

// dot product
Vector2D operator*(const Vector2D& u, const Vector2D& v) {
  return {u.x_ * v.x_, u.y_ * v.y_};
}

float Dot(const Vector2D& u, const Vector2D& v) {
  return static_cast<float>(u.x_ * v.x_ + u.y_ * v.y_);
}

/*
 * scalar multiplication
 */
Vector2D operator*(float s, const Vector2D& u) {
  return Vector2D(s * u.x_, s * u.y_);
}

Vector2D operator*(const Vector2D& u, float s) {
  return Vector2D(s * u.x_, s * u.y_);
}

/*
 * scalar devision
 */
Vector2D operator/(const Vector2D& u, float s) {
  return Vector2D(u.x_ / s, u.y_ / s);
}

bool operator==(const Vector2D& u, const Vector2D& v) {
  return CMP(u.x_, v.x_) && CMP(u.y_, v.y_);
}

bool operator!=(const Vector2D& u, const Vector2D& v) { return !(u == v); }

float Magnitude(const Vector2D& v) { return sqrtf(Dot(v, v)); }
float MagnitudeSq(const Vector2D& v) { return Dot(v, v); }

Vector2D Normalized(const Vector2D& v) { return v.Normalized(); }

float Angle(const Vector2D& u, const Vector2D& v) {
  float m = sqrtf(MagnitudeSq(u) * MagnitudeSq(v));
  return acos(Dot(u, v) / m);
}

Vector2D Project(const Vector2D& len, const Vector2D& dir) {
  // Proj = Dot(a, b) * b / (||B|| * ||B||)
  float dot = Dot(len, dir);
  float magSq = MagnitudeSq(dir);
  return dir * (dot / magSq);
}

Vector2D Perpendicular(const Vector2D& len, const Vector2D& dir) {
  return len - Project(len, dir);
}

Vector2D Reflection(const Vector2D& v, const Vector2D& normal) {
  float d = Dot(v, normal);
  return v - 2.0f * d * normal;
}

/*
 * triple scalar product
 * s = u dot (v cross w)
 */
Vector2D TripleScalarProduct(const Vector2D& u, const Vector2D& v,
                             const Vector2D& w) {
  return u * (v ^ w);
}
}  // namespace math