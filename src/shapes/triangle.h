#ifndef ISHI_SHAPES_TRIANGLE_H_
#define ISHI_SHAPES_TRIANGLE_H_

#include <core/point.h>
#include <shapes/shape.h>

namespace ishi {

class Triangle : public Shape {
 private:
  Point *p1, *p2, *p3;

 public:
  Triangle(const Transform* o2w, const Transform* w2o);

  virtual BBox BoundingBox();
};

}  // namespace ishi

#endif
