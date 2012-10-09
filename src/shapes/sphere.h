#ifndef SHAPES_SPHERES_H_
#define SHAPES_SPHERES_H_

#include <core/point.h>

namespace ishi {

namespace shp {

class Sphere {
 public:
  float r;    // radius
  Point c;    // center

 public:
  Sphere(const Point &center, const float &radius);
};
}

}  // namespace ishi

#endif
