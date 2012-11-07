#include <shapes/triangle.h>

namespace ishi {

Triangle::Triangle(Transform* o2w, Point* pt1, Point* pt2, Point* pt3 )
    : ObjectToWorld(o2w) , p1(pt1), p2(pt2), p3(pt3) {}

/**
 * Transform the points constituting the triangle to world space first,
 * then compute the bounding box directly to world space.
 */
BBox Triangle::ObjectBound() {
  BBox b = BBox(*ObjectToWorld(*p1), *p2);
  return b;
}

}  // namespace ishi
