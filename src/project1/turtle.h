#ifndef TURTLE_TURTLE_H_
#define TURTLE_TURTLE_H_

#include <vector>
#include <core/geometry.h>
#include <core/common.h>
#include <core/color.h>

class TurtleImpl;

class Turtle {
private:
  static TurtleImpl* impl;

public:
  Turtle();
  Turtle(std::vector< Point > *points_, std::vector< Color > *colors_);

  void forward(float distance);
  void right(float deg);
  void left(float deg);
  void origin();
  void up();
  void down();

  /// Destroy the trace list and return the turtle to the origin.
  /// Mainly for testing purpose.
  void reset();
};

#endif