#include <core/point.h>
#include <physics/sphere.h>
#include <physics/collision.h>

namespace ishi {

namespace phy {

Sphere::Sphere(float mass, float radius, float cx, float cy)
    : m(mass), c(cx, cy) {}

Sphere::Sphere(float mass, float radius, float cx, float cy, float cz)
    : m(mass), c(cx, cy, cz), r(radius) {}

float Sphere::Mass() const {
  return m;
}

Point Sphere::Barycenter() const {
  return c;
}

Vector Sphere::Velocity() const {
  return v;
}

Vector Sphere::Spin() const {
  return s;
}

CollisionData* Sphere::Collide(const Sphere &s) const {
  // Determine to see if we actually have a collision or not
  float d = Distance(c, s.c);
  if ((d < r) && (d < s.r)) {
    // No collision
    return 0;
  } else {
    // Construct and return collision data
    CollisionData *cd = new CollisionData();
    cd->Register(this);
    cd->Register(&s);
    // Linearly interpolate between centers, using radii as weights , to get
    // point of collision
    Point poc = (r/(r+s.r)) * c + (1-(r/(r+s.r))) * s.c;
    cd->poc.push_back(&poc);
    return cd;
  }
}
}

}  // namespace ishi

