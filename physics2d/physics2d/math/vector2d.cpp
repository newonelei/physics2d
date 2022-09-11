#include "vector2d.h"
#include "math/float_utils.h"

namespace math {
Vector2D Vector2D::Zero = Vector2D();

Vector2D::Vector2D(void) : x_(0.0f), y_(0.0f) {}

inline Vector2D::Vector2D(float xi, float yi) : x_(xi), y_(yi) {}

inline float Vector2D::Magnitude(void) const {
  return sqrtf(Dot(*this, *this));
}

inline void Vector2D::Normalize(void) {
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

inline void Vector2D::Reverse(void) {
  x_ = -x_;
  y_ = -y_;
}

inline Vector2D& Vector2D::operator+=(const Vector2D& u) {
  x_ += u.x_;
  y_ += u.y_;
  return *this;
}

inline Vector2D& Vector2D::operator-=(const Vector2D& u) {
  x_ -= u.x_;
  y_ -= u.y_;
  return *this;
}

inline Vector2D& Vector2D::operator*=(const Vector2D& u) {
  x_ *= u.x_;
  y_ *= u.y_;
  return *this;
}

inline Vector2D& Vector2D::operator/=(const Vector2D& u) {
  x_ /= u.x_;
  y_ /= u.y_;
  return *this;
}

inline Vector2D Vector2D::operator-(void) { return Vector2D(-x_, -y_); }

inline Vector2D operator+(const Vector2D& u, const Vector2D& v) {
  return Vector2D(u.x_ + v.x_, u.y_ + v.y_);
}

inline Vector2D operator-(const Vector2D& u, const Vector2D& v) {
  return Vector2D(u.x_ - v.x_, u.y_ - v.y_);
}

/*
 * vector cross product
 */
inline float operator^(const Vector2D& u, const Vector2D& v) {
  return static_cast<float>(u.x_ * v.y_ - u.y_ * v.x_);
}

// dot product
inline float operator*(const Vector2D& u, const Vector2D& v) {
  return static_cast<float>(u.x_ * v.x_ + u.y_ * v.y_);
}

inline float Dot(const Vector2D& u, const Vector2D& v) { return u * v; }

/*
 * scalar multiplication
 */
inline Vector2D operator*(float s, const Vector2D& u) {
  return Vector2D(s * u.x_, s * u.y_);
}

inline Vector2D operator*(const Vector2D& u, float s) {
  return Vector2D(s * u.x_, s * u.y_);
}

/*
 * scalar devision
 */
inline Vector2D operator/(const Vector2D& u, float s) {
  return Vector2D(u.x_ / s, u.y_ / s);
}

bool operator==(const Vector2D& u, const Vector2D& v) {
  return CMP(u.x_, v.x_) && CMP(u.y_, v.y_);
}

bool operator!=(const Vector2D& u, const Vector2D& v) { return !(u == v); }

float Magnitude(const Vector2D& v) { return sqrtf(v * v); }
float MagnitudeSq(const Vector2D& v) { return v * v; }

Vector2D Normalized(const Vector2D& v) { return v.Normalized(); }


inline float Angle(const Vector2D& u, const Vector2D& v)
{
	float m = sqrtf(MagnitudeSq(u) * MagnitudeSq(v));
	return acos(Dot(u, v) / m);
}
/*
 * triple scalar product
 * s = u dot (v cross w)
 */
inline Vector2D TripleScalarProduct(const Vector2D& u, const Vector2D& v,
                                    const Vector2D& w) {
  return u * (v ^ w);
}
}  // namespace math