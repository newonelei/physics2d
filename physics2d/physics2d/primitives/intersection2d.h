#pragma once

#include "circle2d.h"
#include "line2d.h"
#include "oriented_rectangle2d.h"
#include "point2d.h"
#include "rectangle2d.h"
#include "circle2d.h"

#ifndef _H_2D_INTERSECTION_
#define _H_2D_INTERSECTION_

namespace primitives {


#define PointLine(point, line) PointOnLine(point, line)
#define LinePoint(line, point) PointOnLine(point, line)
#define CircleLine(circle, line) LineCircle(line, circle)
#define RectangleLine(rectangle, line) LineRectangle(line, rectangle)
#define OrientedRectangleLine(rectangle, line) LineOrientedRectangle(line, rectangle)

// point containment
bool PointOnLine(const Point2D& point, const Line2D& line);
bool PointInCircle(const Point2D& point, const Circle2D& circle);
bool PointInRectangle(const Point2D&, const Rectangle2D& rectangle);
bool PointInOrientedRectangle(const Point2D&,
                              const OrientedRectangle2D& rectangle);

// line intersection
bool LineCircle(const Line2D& line, const Circle2D& circle);
bool LineRectangle(const Line2D& line, const Rectangle2D& rect);
bool LineOrientedRectangle(const Line2D& line, const OrientedRectangle2D& rect);

// 2d collisions
bool CircleCircle(const Circle2D& c1, const Circle2D& c2);
}  // namespace primitives

#endif  // _H_2D_INTERSECTION_