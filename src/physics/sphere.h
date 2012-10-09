#ifndef PHYSICS_SPHERE_H_
#define PHYSICS_SPHERE_H_

#include <core/point.h>
#include <core/vector.h>
#include <physics/object.h>

namespace ishi {

namespace phy {

class CollisionData;

class Sphere : public Object {
 public:
  float r;    // radius
  Point c;    // center
  float m;    // mass
  Vector v;   // velocity
  Vector s;   // spin

 public:
  /// Initialize a physics sphere on the xy plane
  Sphere(float mass, float radius, float cx, float cy);

  /// Initialize a physics sphere in space
  Sphere(float mass, float radius, float cx, float cy, float cz);

  virtual float Mass() const;

  virtual Point Barycenter() const;

  virtual Vector Velocity();

  virtual Vector Spin() const;

  CollisionData* Collide(const Sphere &s) const;
};
}

}  // namespace ishi

#endif
