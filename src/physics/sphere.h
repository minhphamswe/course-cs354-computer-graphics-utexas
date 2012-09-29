#ifndef PHYSICS_SPHERE_H_
#define PHYSICS_SPHERE_H_

#include <core/point.h>
#include <core/vector.h>
#include <physics/object.h>

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

  virtual float Mass();

  virtual Point Barycenter();

  virtual Vector Velocity();

  virtual Vector Spin();

  CollisionData* Collide(Sphere& s);
};

}

#endif
