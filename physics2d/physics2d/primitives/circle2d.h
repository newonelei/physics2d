#pragma once

#include "point2d.h"

#ifndef _H_2D_CIRCLE_
#define _H_2D_CIRCLE_

namespace primitives {
typedef struct Circle2D {
  Point2D position_;
  float radius_;

  // create a default circle at original point with 1.0f radius(unit circle at
  // original point)
  inline Circle2D() : radius_{1.0f} {}
  inline Circle2D(const Point2D& p, float r) : position_{p}, radius_{r} {}
} Circle2D;

}  // namespace primitives

#endif  //_H_2D_CIRCLE_
