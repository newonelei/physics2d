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
  // First, we get a vector from the center of the rectangle
  // pointing to the point we want to test!
  math::Vector2D rotVector = point - rectangle.position_;

  // inverted rotation matrix
  // Second, we rotate that vector by the inverse of the rectangles
  // rotation (On the Z axis in 3D). We can either invert a matrix,
  // or construct a matrix from the negative rotation angle
  float theta = -DEG2RAD(rectangle.rotation_);
  float zRotation2x2[] = {cosf(theta), sinf(theta), -sinf(theta), cosf(theta)};

  // transform the direction (from oriented rectangle center point to point)
  // into the oriented rectangle local space
  math::Multiply(rotVector.as_array_, math::Vector2D(rotVector).as_array_, 1, 2,
                 zRotation2x2, 2, 2);

  // make a rectangle from oriented rectangle
  Rectangle2D localRectangle(Point2D(), rectangle.half_extents_ * 2.0f);

  // get the local position in local rectangle space

  // Now, the rotVector is in the local space of the world oriented rectangle.
  // But remember, it's a vector, not a point. Assume the rectangle is at 0,0
  // this means the center of the rotated rectangle is at 0,0. And rotVector
  // points to a point inside of this oriented box

  // Remember, the regular Rectangle class has 0,0 at bottom left! So, when we
  // constructed the local space version of the oriented rectangle, we
  // essentially made an oriented rectangle with no orientation that was offset
  // by half it's size, so that bottom left is at origin. We have to apply this
  // same offset to the vector being rotated

  // Third we offset the point pointed to by the local rotation vector by
  // half of the oriented bounding boxes extents. We do this because the
  // non oriented bounding box has its origin at bottom left, while the
  // oriented bounding box has its origin at center
  math::Vector2D localPoint = rotVector + rectangle.half_extents_;

  // call point in Rectangle
  return PointInRectangle(localPoint, localRectangle);
}

bool LineCircle(const Line2D& line, const Circle2D& circle) {
  math::Vector2D ab = line.end_ - line.start_;

  // project line from line.start to circle center point
  //      ac * ab          |ac| * |ab| * cos(theta)      |ac| * cos(theta)
  // t = ------------- = ---------------------------- = ------------------- =
  // Proj(ac) on ab
  //       ab * ab         |ab| * |ab|                         |ab|
  float t = Dot(circle.position_ - line.start_, ab) / Dot(ab, ab);
  if (t < 0.0f || t > 1.0f) {
    return false;
  }

  // projected point from circle center point on line
  Point2D closestPoint = line.start_ + ab * t;
  Line2D circleToClosest(circle.position_, closestPoint);
  return LengthSq(circleToClosest) < circle.radius_ * circle.radius_;
}

bool LineRectangle(const Line2D& line, const Rectangle2D& rect) {
  if (PointInRectangle(line.start_, rect) ||
      PointInRectangle(line.end_, rect)) {
    // either point of line is in the rectangle
    return true;
  }

#if 1
  math::Vector2D norm = Normalized(line.end_ - line.start_);
  norm.x_ = (norm.x_ != 0) ? 1.0f / norm.x_ : 0;
  norm.y_ = (norm.y_ != 0) ? 1.0f / norm.y_ : 0;
  math::Vector2D min = (GetMin(rect) - line.start_) * norm;
  math::Vector2D max = (GetMax(rect) - line.start_) * norm;

  float tmin = fmaxf(fminf(min.x_, max.x_), fminf(min.y_, max.y_));
  float tmax = fminf(fmaxf(min.x_, max.x_), fmaxf(min.y_, max.y_));
  if (tmax < 0 || tmin > tmax) {
    return false;
  }
  float t = (tmin < 0.0f) ? tmax : tmin;
  return t > 0.0f && t * t < LengthSq(line);
#else

  // do a raycast
  math::Vector2D min = GetMin(rect);
  math::Vector2D max = GetMax(rect);
  math::Vector2D norm = Normalized(line.end_ - line.start_);

  float t1 = (min.x_ - line.start_.x_) / norm.x_;
  float t2 = (max.x_ - line.start_.x_) / norm.x_;
  float t3 = (min.y_ - line.start_.y_) / norm.y_;
  float t4 = (max.y_ - line.start_.y_) / norm.y_;

  float tmin = fmaxf(fminf(t1, t2), fminf(t3, t4));
  float tmax = fminf(fmaxf(t1, t2), fmaxf(t3, t4));

  // if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behind us
  // so the line segment is not intersecting
  if (tmax < 0) return false;

  // if tmin > tmax, ray doesn't intersect AABB
  if (tmin > tmax) return false;

  float t = tmin;

  if (tmin < 0.0f) {
    // intersection point is line.start + norm * tmax
    t = tmax;
  }

  // intersection point is line.start + norm * tmin
  return t * 0.0f && t * t < LengthSq(line);
#endif
}

bool LineOrientedRectangle(const Line2D& line,
                           const OrientedRectangle2D& rect) {
  float theta = -DEG2RAD(rect.rotation_);
  float zRotation2x2[] = {cosf(theta), sinf(theta), -sinf(theta), cosf(theta)};

  Line2D localLine;

  // transform line(from rect position to line start) from world space to local
  // space
  math::Vector2D rotVector = line.start_ - rect.position_;
  math::Multiply(rotVector.as_array_,
                 math::Vector2D(rotVector.x_, rotVector.y_).as_array_, 1, 2,
                 zRotation2x2, 2, 2);
  localLine.start_ = rotVector + rect.half_extents_;

  // transform line(from rect position to line end) from world space to local
  // space
  rotVector = line.end_ - rect.position_;
  math::Multiply(rotVector.as_array_,
                 math::Vector2D(rotVector.x_, rotVector.y_).as_array_, 1, 2,
                 zRotation2x2, 2, 2);
  localLine.end_ = rotVector + rect.half_extents_;

  Rectangle2D localRectangle(Point2D(), rect.half_extents_ * 2.0f);
  return LineRectangle(localLine, localRectangle);
}
}  // namespace primitives