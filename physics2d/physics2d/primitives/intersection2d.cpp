#include "intersection2d.h"

#include "math/float_utils.h"
#include "math/matrices.h"

namespace primitives {
bool PointOnLine(const Point2D& point, const Line2D& line) {
  // y = Mx + B, M is slope, B  is y-intercept

  // find the slope
  float dy = line.end_.y_ - line.start_.y_;
  float dx = line.end_.x_ - line.start_.x_;
  float M = dy / dx;

  // find Y-intercept, B = y - mx
  float B = line.start_.y_ - M * line.start_.x_;

  // Check line equation
  return CMP(point.y_, M * point.x_ + B);
}

bool PointInCircle(const Point2D& point, const Circle2D& circle) {
  Line2D line(point, circle.position_);
  return LengthSq(line) < circle.radius_;
}

bool PointInRectangle(const Point2D& point, const Rectangle2D& rectangle) {
  math::Vector2D min = GetMin(rectangle);
  math::Vector2D max = GetMax(rectangle);

  return min.x_ <= point.x_ && min.y_ <= point.y_ && point.x_ <= max.x_ &&
         point.y_ <= max.y_;
}

bool PointInOrientedRectangle(const Point2D& point,
                              const OrientedRectangle2D& rectangle) {
  // direction from oriented rectangle center point to point
  math::Vector2D rotVector = point - rectangle.position_;

  // inverted rotation matrix
  float theta = -DEG2RAD(rectangle.rotation_);
  float zRotation2x2[] = {cosf(theta), sinf(theta), -sinf(theta), cosf(theta)};

  // transform the direction (from oriented rectangle center point to point)
  // into the oriented rectangle local space
  math::Multiply(rotVector.as_array_, math::Vector2D(rotVector).as_array_, 1, 2,
                 zRotation2x2, 2, 2);

  // make a rectangle from oriented rectangle
  Rectangle2D localRectangle(Point2D(), rectangle.half_extents_ * 2.0f);

  // get the local position in local rectangle space
  math::Vector2D localPoint = rotVector + rectangle.half_extents_;

  // call point in Rectangle
  return PointInRectangle(localPoint, localRectangle);
}
}  // namespace primitives