#pragma once

#include "math/vector2d.h"
#include "point2d.h"

#ifndef _H_2D_RECTANGLE_
#define _H_2D_RECTANGLE_
namespace primitives {
/*
There are several ways to represent a rectangle: using a Min and Max point,
using a Center and half-extents, or using a Position and a Size:
*/
typedef struct Rectangle2D {
  // original position of rectangle 2d
  Point2D origin_;
  // full size of rectangle
  math::Vector2D size_;

  // unit rectangle with size 1,1 at origin point
  inline Rectangle2D() : size_(1, 1) {}
  inline Rectangle2D(const Point2D& o, const math::Vector2D& s)
      : origin_{o}, size_{s} {}
} Rectangle2D;

math::Vector2D GetMin(const Rectangle2D& rect);
math::Vector2D GetMax(const Rectangle2D& rect);

Rectangle2D FromMinMax(const math::Vector2D& min, const math::Vector2D& max);
}  // namespace primitives
#endif  // _H_2D_RECTANGLE_
