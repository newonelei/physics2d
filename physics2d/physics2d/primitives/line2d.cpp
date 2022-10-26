#include "line2d.h"
#include "math/vector2d.h"

namespace primitives {
float Length(const Line2D& line) {
  return math::Magnitude(line.end_ - line.start_);
}

float LengthSq(const Line2D& line) {
  return math::MagnitudeSq(line.end_ - line.start_);
}
}  // namespace primitives