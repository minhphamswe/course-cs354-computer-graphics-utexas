#ifndef ISHI_SHAPES_TRIANGLEMESH_H_
#define ISHI_SHAPES_TRIANGLEMESH_H_

#include <shapes/shape.h>


namespace ishi {

class Point;
class Vector;
class Normal;

class TriangleMesh : public Shape {
 public:
  int NumVerts();

  /// Return v[i], a counter-clockwise-ordered vertex
  Point Vertex(int i);

  /// Return the edge e[i] formed by v[i+1] - v[i]
  Vector Edge(int i);

  /// Return the normal vector to the edge e[i]
  Normal Normal(int i);
};

void Render(const TriangleMesh &tm);

}  // namespace ishi

#endif
