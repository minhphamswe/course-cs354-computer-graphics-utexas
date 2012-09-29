#ifndef __BALL_H__
#define __BALL_H__

#include "./geom2.h"

#include <physics/sphere.h>
#include <core/color.h>
#include <shapes/disk.h>

// A handy Ball class
class Ball {
 public:
  phy::Sphere psph;  // Physical sphere
  Disk disk;
  Color color;

 public:
  /// Initialize a ball at the center of the world
  Ball(float r, float g, float b);

  /// Initialize a ball on the xy plane
  Ball(float r, float g, float b, float x, float y);

};

#endif
