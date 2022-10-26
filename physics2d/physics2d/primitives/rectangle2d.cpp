#include "rectangle2d.h"
#include <cmath>

namespace primitives {
math::Vector2D GetMin(const Rectangle2D& rect) {
  Point2D p1 = rect.origin_;
  Point2D p2 = rect.origin_ + rect.size_;

  return math::Vector2D(fminf(p1.x_, p2.x_), fminf(p1.y_, p2.y_));
}

math::Vector2D GetMax(const Rectangle2D& rect) {
  Point2D p1 = rect.origin_;
  Point2D p2 = rect.origin_ + rect.size_;

  return math::Vector2D(fmaxf(p1.x_, p2.x_), fmaxf(p1.y_, p2.y_));
}

Rectangle2D FromMinMax(const math::Vector2D& min, const math::Vector2D& max) {
  return Rectangle2D(min, max - min);
}
}  // namespace primitives