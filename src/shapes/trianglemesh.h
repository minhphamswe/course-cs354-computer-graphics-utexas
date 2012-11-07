#ifndef ISHI_SHAPES_TRIANGLEMESH_H_
#define ISHI_SHAPES_TRIANGLEMESH_H_

#include <core/point.h>
#include <core/vector.h>
#include <core/bbox.h>
#include <shapes/shape.h>

#include <vector>

namespace ishi {

class TriangleMesh : public Shape {
 private:
  Transform o2w;
  Transform w2o;
  BBox bbox;
  std::vector<Point> vertices;
  std::vector<Vector> normals;
  std::vector<Point*> triangles;

 public:
  Transform *ObjectToWorld;
  Transform *WorldToObject;

 public:
  TriangleMesh();

  virtual ~TriangleMesh();

  int NumVerts();

  /// Add a new vertex with the given coordinates to the mesh
  void AddVertex(float px, float py, float pz);

  /// Add a polygon that points to vertices at the given indices to the mesh
  void AddPolygon(int v1, int v2, int v3);

  /// Compute the normal at each vertex
  void ComputeNormal();

  /// Return the vertex at the index i
  Point Vertex(int i);

  /// Return the normal vector at the index i
  Vector Normal(int i);

  virtual BBox ObjectBound() const;
};

}  // namespace ishi

#endif
