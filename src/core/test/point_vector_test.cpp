#include <core/geometry.h>
#include <UnitTest++/UnitTest++.h>

using namespace ishi;

TEST(PointVectorAdditionSubtraction) {
  Point p1, p2, p;
  Vector v1, v2, v;

  p1 = Point(1, 2, 3);
  p2 = Point(4, 5, 6);
  v1 = Vector(4, 5, 6);
  v2 = Vector(1, 2, 3);

  p = p1 + v1;
  CHECK_EQUAL(p.x, 5);
  CHECK_EQUAL(p.y, 7);
  CHECK_EQUAL(p.z, 9);

  p = p2 + v2;
  CHECK_EQUAL(p.x, 5);
  CHECK_EQUAL(p.y, 7);
  CHECK_EQUAL(p.z, 9);
}

