#ifndef PHYSICS_OBJECT_H_
#define PHYSICS_OBJECT_H_

#include <core/vector.h>
#include <core/point.h>

namespace ishi {

namespace phy {
/// Physically collidable object
class Object {
 public:
  virtual ~Object() {}

  virtual float Mass() = 0;
  virtual Point Barycenter() = 0;
  virtual Vector Velocity() = 0;
  virtual Vector Spin() = 0;
};
}

}  // namespace ishi

#endif
