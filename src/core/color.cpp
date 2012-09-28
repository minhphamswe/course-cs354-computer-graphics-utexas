#include <core/color.h>

Color::Color(float rr, float gg, float bb)
    : r(rr), g(gg), b(bb), a(1.0f) {}

Color::Color(float rr, float gg, float bb, float aa)
    : r(rr), g(gg), b(bb), a(aa) {}
