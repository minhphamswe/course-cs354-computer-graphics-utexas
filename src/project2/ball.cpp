#include "./ball.h"

#include <core/point.h>
#include <core/color.h>

// Handy ball class implementation
const float radius = 50;    // Common radius for all balls
const float mass = 50;      // Common mass for all balls

Ball::Ball (float r, float g, float b)
    : color(r, g, b), disk(radius, Point()), psph(mass, radius, 0, 0) {}

Ball::Ball (float r, float g, float b, float x, float y)
    : color(r, g, b), disk(radius, Point()), psph(mass, radius, x, y) {}


