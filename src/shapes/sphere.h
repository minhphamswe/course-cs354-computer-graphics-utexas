#ifndef SHAPES_SPHERES_H_
#define SHAPES_SPHERES_H_

#include <core/point.h>

namespace shp {

class Sphere {
 public:
  float r;    // radius
  Point c;    // center

 public:
  Sphere(Point center, float radius);
};

}

#endif