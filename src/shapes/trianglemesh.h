#ifndef ISHI_SHAPES_TRIANGLEMESH_H_
#define ISHI_SHAPES_TRIANGLEMESH_H_

#include <core/point.h>
#include <core/vector.h>
#include <core/bbox.h>
#include <shapes/shape.h>
// #include <rendering/GLRenderer.h>
#include <rendering/renderer.h>
#include <rendering/GLRenderer.h>

#include <vector>

namespace ishi {

// class GLRenderer;

class TriangleMesh : public Shape {
 private:
  Transform o2w;
  Transform w2o;
  BBox bbox;
  std::vector<Point> vertices;
  std::vector<Vector> normals;
  std::vector<Point*> triangles;
  std::vector<Point*> quads;

 public:
  const Transform *ObjectToWorld;
  const Transform *WorldToObject;

 public:
  TriangleMesh();

  virtual ~TriangleMesh();

  int NumVerts();

  /// Add a new vertex with the given coordinates to the mesh
  void AddVertex(float px, float py, float pz);

  /// Add a polygon that points to vertices at the given indices to the mesh
  void AddPolygon(const std::vector< int > vertIndices);

  /// Compute the normal at each vertex
  void ComputeNormal();

  /// Return the vertex at the index i
  Point Vertex(int i);

  /// Return the normal vector at the index i
  Vector Normal(int i);

  /// Return the number of vertices in the triangle mesh
  int NumVerts(int i);

  virtual BBox ObjectBound() const;

  virtual void accept(Renderer& r);

  friend class GLRenderer;
};

}  // namespace ishi

#endif
