#include <cmath>

#include "assert.h"
#include "light.h"



using namespace std;

double DirectionalLight::distanceAttenuation(const Vec3d& P) const {
  // distance to light is infinite, so f(di) goes to 0.  Return 1.
  return 1.0;
}


Vec3d DirectionalLight::shadowAttenuation(const Vec3d& P) const {
  // YOUR CODE HERE:
  // You should implement shadow-handling code here.
  ray r = ray(P, this->getDirection(P), ray::SHADOW);
  isect i;
  assert(scene != NULL);
  if (scene->intersect(r, i)) {
    // Ray hit some object
    return Vec3d(0, 0, 0);
  } else {
    // Ray did not hit anything
    return Vec3d(1, 1, 1);
  }
}

Vec3d DirectionalLight::getColor(const Vec3d& P) const {
  // Color doesn't depend on P
  return color;
}

Vec3d DirectionalLight::getDirection(const Vec3d& P) const {
  return -orientation;
}

double PointLight::distanceAttenuation(const Vec3d& P) const {

  // YOUR CODE HERE

  // You'll need to modify this method to attenuate the intensity
  // of the light based on the distance between the source and the
  // point P.  For now, we assume no attenuation and just return 1.0

  // Calculate distance to source
  Vec3d delta = this->position - P;
  double d = delta * delta;

  // Calculate attenuation factor
  double f = (this->constantTerm +
              this->linearTerm * d +
              this->quadraticTerm * d * d);
  if (f != 0)
    f = 1 / f;

  return f;

}

Vec3d PointLight::getColor(const Vec3d& P) const {
  // Color doesn't depend on P
  return color;
}

Vec3d PointLight::getDirection(const Vec3d& P) const {
  Vec3d ret = position - P;
  ret.normalize();
  return ret;
}


Vec3d PointLight::shadowAttenuation(const Vec3d& P) const {
  // YOUR CODE HERE:
  // You should implement shadow-handling code here.
  ray r = ray(P, this->getDirection(P), ray::SHADOW);
  isect i;

  if (scene->intersect(r, i)) {
    // Ray hit some object
    Vec3d isectPoint = r.at(i.t);
    if ((isectPoint - P).length2() < (position - P).length2()) {
      // Object is before light source
//       return Vec3d(0, 0, 0);
      const Material& m = i.getMaterial();
      return m.kt(i);
    }
    else {
      return Vec3d(1, 1, 1);
    }
  } else {
    // Ray did not hit anything
    return Vec3d(1, 1, 1);
  }
}
