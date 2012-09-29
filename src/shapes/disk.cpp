#include <cmath>

#include <shapes/disk.h>
#include <core/point.h>
#include <project2/common.h>

Disk::Disk(float radius)
    : r(radius), c(Point()) {
  verts.push_back(&c);
  for (int theta = PI; theta < 2*PI; theta += PI/4) {
    verts.push_back(new Point(std::cos(theta)*r, std::sin(theta)*r));
  }
}

Disk::Disk(float radius, Point center)
    : r(radius), c(center) {
  verts.push_back(&c);
  for (int theta = PI; theta < 2*PI; theta += PI/4) {
    verts.push_back(new Point(std::cos(theta)*r, std::sin(theta)*r));
  }
}
