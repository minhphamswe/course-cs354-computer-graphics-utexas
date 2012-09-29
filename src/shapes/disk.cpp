#include <cmath>

#include <shapes/disk.h>
#include <core/point.h>
#include <core/transform.h>

Disk::Disk(float radius)
    : r(radius), c(Point()) {
  verts.push_back(c);
  for (float theta = 0; theta < 7; theta += 0.3927) {
    verts.push_back(c + Point(std::cos(theta)*r, std::sin(theta)*r));
  }
  verts.push_back(c);
}

Disk::Disk(float radius, Point center)
    : r(radius), c(center) {
  verts.push_back(c);
  for (float theta = 0; theta <= 7; theta += 0.3927) {
    verts.push_back(c + Point(std::cos(theta)*r, std::sin(theta)*r));
  }
  verts.push_back(c);
}

