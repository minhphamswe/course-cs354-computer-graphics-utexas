#ifndef PHYSICS_COLLISION_H_
#define PHYSICS_COLLISION_H_

#include <vector>

#include <core/vector.h>
#include <core/point.h>

namespace phy {

class Object;

struct CollisionData {
 public:
  std::vector<Object*> objects;
  std::vector<float> masses;
  std::vector<Point> barycenters;
  std::vector<Vector> velocities;
  std::vector<Vector> spins;
  std::vector<Point*> poc;  // Points of collision

  Vector impulse;

 public:
  void Register(Object* obj);
};

class Collision {
  void Act(CollisionData);
};

}

#endif
