#pragma once

#include "line2d.h"
#include "point2d.h"
#include "circle2d.h"
#include "rectangle2d.h"
#include "oriented_rectangle2d.h"

#ifndef _H_2D_INTERSECTION_
#define _H_2D_INTERSECTION_

namespace primitives {
bool PointOnLine(const Point2D& point, const Line2D& line);
bool PointInCircle(const Point2D& point, const Circle2D& circle);
bool PointInRectangle(const Point2D&, const Rectangle2D& rectangle);
bool PointInOrientedRectangle(const Point2D&, const OrientedRectangle2D& rectangle);
}

#endif  // _H_2D_INTERSECTION_