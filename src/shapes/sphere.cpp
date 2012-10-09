#include <shapes/sphere.h>

#include <core/point.h>
#include <core/vector.h>

namespace ishi {

namespace shp {

Sphere::Sphere(const Point &center, const float &radius)
    : c(center), r(radius) {}
}

}  // namespace ishi
