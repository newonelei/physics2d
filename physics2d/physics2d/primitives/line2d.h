#pragma once

#include "point2d.h"

#ifndef _H_2D_LINE_
#define _H_2D_LINE_

namespace primitives {
typedef struct Line2D {
  Point2D start_;
  Point2D end_;

  inline Line2D() = default;
  inline Line2D(const Point2D& s, const Point2D& e) : start_{s}, end_{e} {}
} Line2D;

float Length(const Line2D& line);
float LengthSq(const Line2D& line);

}  // namespace primitives

#endif // _H_2D_LINE_