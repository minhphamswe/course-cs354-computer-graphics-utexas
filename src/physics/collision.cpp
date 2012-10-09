#include <physics/collision.h>
#include <physics/object.h>

namespace ishi {

namespace phy {
void CollisionData::Register(Object* obj) {
  objects.push_back(obj);
  masses.push_back(obj->Mass());
  barycenters.push_back(obj->Barycenter());
  velocities.push_back(obj->Velocity());
  spins.push_back(obj->Spin());
}
}

}  // namespace ishi
