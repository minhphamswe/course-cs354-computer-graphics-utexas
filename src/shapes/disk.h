#ifndef SHAPES_DISK_H_
#define SHAPES_DISK_H_

#include <core/point.h>

#include <vector>

namespace ishi {

class Point;

struct Disk {
 public:
  float r;    // radius
  Point c;    // center
  std::vector<Point> verts;

 public:
  /// Create a disk at the origin, parallel to the x-y plane
  explicit Disk(float radius);

  /// Create a disk at on the x-y plane
  Disk(float radius, Point center);
};

}  // namespace ishi

#endif
