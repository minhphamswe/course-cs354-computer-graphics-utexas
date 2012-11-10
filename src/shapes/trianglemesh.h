#ifndef ISHI_SHAPES_TRIANGLEMESH_H_
#define ISHI_SHAPES_TRIANGLEMESH_H_

#include <core/point.h>
#include <core/vector.h>
#include <core/bbox.h>
#include <core/shape.h>
#include <core/imaterial.h>

#include <core/renderer.h>
#include <rendering/GLRenderer.h>

#include <vector>

namespace ishi {

class TriangleMesh : public Shape {
 private:
  BBox bbox;        // Object bounding box

  std::vector<Point> vertices;          // Vertex coordinates
  std::vector<Vector> normals;          // Vertex normals
  std::vector<int> triangles;           // Vertex indices for triangles
  std::vector<int> quads;               // Vertex indices for quads

  std::vector<Point> textures;          // Texture coordinates
  std::vector<int> triangle_textures;   // Texture indices for triangles
  std::vector<int> quad_textures;       // Texture indices for quads

  std::vector<int> material_mapping;    // Mapping from polygon to material
  std::vector<ishi::Texture> materials;      // Collection of materials

 public:
//   Transform *ObjectToWorld;
//   Transform *WorldToObject;

 public:
  TriangleMesh(Transform *o2w, Transform *w2o);

  virtual ~TriangleMesh();

  /// Add a new vertex with the given coordinates to the mesh
  void AddVertex(float px, float py, float pz);

  /// Add a polygon that points to vertices at the given indices to the mesh
  void AddPolygon(const std::vector<int> vertIndices);

  /// Compute the normal at each vertex
  void ComputeNormal();

  /// Return the vertex at the index i
  Point Vertex(int i) const;

  /// Return the normal vector at the index i
  Vector Normal(int i) const;

  /// Return the number of vertices in the triangle mesh
  int NumVerts();

  virtual BBox ObjectBound() const;

  virtual void accept(const Renderer& r);

  /// Add a new texture coordinate to the mesh
  void AddTextureVertex(float tx, float ty, float tz);

  /// Add a polygon that points to textures at the given indices to the mesh
  void AddPolygonTexture(const std::vector<int> textIndices);

  /// Load mapping from polygon to material
  void LoadMaterialMapping(const std::vector<int> mapping);

  /// Add a new material
  void AddMaterial(const Texture &material);

  friend class GLRenderer;
};

}  // namespace ishi

#endif
