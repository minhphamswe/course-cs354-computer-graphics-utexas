#ifndef ISHI_SHAPES_TRIANGLE_H_
#define ISHI_SHAPES_TRIANGLE_H_

#include <core/point.h>
#include <shapes/shape.h>

namespace ishi {

class Triangle : public Shape {
 private:
  Transform *ObjectToWorld;
  Point *p1, *p2, *p3;

 public:
  Triangle(Transform* o2w, Point* pt1, Point* pt2, Point* pt3);

  virtual BBox ObjectBound() const;

};

}  // namespace ishi

#endif
