#include <shapes/shape.h>
#include <shapes/trianglemesh.h>

namespace ishi {

BBox Shape::WorldBound() const {
  return *ObjectToWorld(ObjectBound());
}

}  // namespace ishi
