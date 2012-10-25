#include <shapes/triangle.h>

namespace ishi {

Triangle::Triangle(const Transform* o2w, const Transform* w2o): Shape(o2w, w2o)
{

}

/**
 * Transform the points constituting the triangle to world space first,
 * then compute the bounding box directly to world space.
 */
BBox Triangle::BoundingBox() {
  BBox b = BBox(*ObjectToWorld(*p1), *p2);
  return ishi::Shape::BoundingBox();
}

}  // namespace ishi
