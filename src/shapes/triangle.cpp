#include <shapes/triangle.h>

namespace ishi {

Triangle::Triangle(Transform* o2w, Transform* w2o,
                   Point* pt1, Point* pt2, Point* pt3 )
    : Shape(o2w, w2o), p1(pt1), p2(pt2), p3(pt3) {}

/**
 * Transform the points constituting the triangle to world space first,
 * then compute the bounding box directly to world space.
 */
BBox Triangle::ObjectBound() {
  BBox b = Union(BBox(*p1, *p2), *p3);
  return b;
}

}  // namespace ishi
