#pragma once

#include "math/vector2d.h"
#include "point2d.h"

#ifndef _H_2D_ORIENTED_RECTANGLE_
#define _H_2D_ORIENTED_RECTANGLE_

namespace primitives {
typedef struct OrientedRectangle2D {
  // center position
  Point2D position_;
  // half extents on 2 axises
  math::Vector2D half_extents_;
  // rotation of rectangle
  float rotation_;

  // default constructor : unit length rectangle at origin with no rotation
  inline OrientedRectangle2D() : half_extents_(1.0f, 1.0f), rotation_(0.0f) {}

  // a constructor that takes a center point and half-extents with no rotation
  inline OrientedRectangle2D(const Point2D& p, const math::Vector2D& e)
      : position_{p}, half_extents_{e}, rotation_{0.0f} {}

  // full constructor
  inline OrientedRectangle2D(const Point2D& p, const math::Vector2D& ext,
                             float rot)
      : position_{p}, half_extents_{ext}, rotation_{rot} {}
} OrientedRectangle2D;
}  // namespace primitives

#endif  // _H_2D_ORIENTED_RECTANGLE_