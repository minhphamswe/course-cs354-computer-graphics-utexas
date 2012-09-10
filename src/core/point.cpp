#include <core/point.h>

Point::Point()
    : x(0), y(0), z(0) {}

Point::Point(float xx, float yy)
    : x(xx), y(yy), z(0) {}

Point::Point(float xx, float yy, float zz)
    : x(xx), y(yy), z(zz) {}
