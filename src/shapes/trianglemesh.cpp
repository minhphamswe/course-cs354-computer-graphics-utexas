#include <shapes/trianglemesh.h>
#include <core/common.h>
#include <core/point.h>
#include <core/vector.h>
#include <core/transform.h>
#include <core/shape.h>

#include <shapes/triangle.h>
#include <shapes/quad.h>

#include <vector>

namespace ishi {

TriangleMesh::TriangleMesh(Transform *o2w, Transform *w2o)
    : Shape(o2w, w2o) {
  polygons.clear();
}

TriangleMesh::~TriangleMesh() {}

void TriangleMesh::AddVertex(float px, float py, float pz) {
//   printf("Adding vertex ...\n");
//   printf("Geometry Vertex: (%f, %f, %f)\n", v[0], v[1], v[2]);
  // Initialize the point
  Point p(px, py, pz);

  // Push point to vertex list, a degenerate normal to the normal list
  vertices.push_back(p);
  normals.push_back(Vector());

  // Update the bounding box
  bbox = Union(bbox, p);

  // Update the Object-to-World transformation matrix
  Point center = (bbox.pMin + bbox.pMax)/2;
  *ObjectToWorld = Translate(Point() - center);
  *WorldToObject = Inverse(*ObjectToWorld);
}

void TriangleMesh::AddTextureVertex(float tx, float ty, float tz) {
  Point t(tx, ty, tz);
  textures.push_back(t);
}

void TriangleMesh::AddPolygon(const std::vector<int> vertIndices) {
//   printf("Adding polygon ...\n");
  Assert(vertIndices.size() >= 3);

  int v1, v2, v3, v4;

  if (vertIndices.size() == 3) {
    v1 = vertIndices[0];
    v2 = vertIndices[1];
    v3 = vertIndices[2];

    Triangle t = Triangle(ObjectToWorld, WorldToObject, this, v1, v2, v3,
                          polygons.size());

    // Compute the normalized normal of the triangle
    Vector n = t.Normal();

    // Add the normal to the normal list corresponding to each point
    normals[v1] += n;
    normals[v2] += n;
    normals[v3] += n;

    // Add vertices to the triangle vertex list
    triangles.push_back(t);
    polygons.push_back(&(triangles.back()));

  } else if (vertIndices.size() == 4) {
    v1 = vertIndices[0];
    v2 = vertIndices[1];
    v3 = vertIndices[2];
    v4 = vertIndices[3];

    Quad q = Quad(ObjectToWorld, WorldToObject, this, v1, v2, v3, v4,
                  polygons.size());

    // Compute the normalized normal of the triangle
    Vector n = q.Normal();

    // Add the normal to the normal list corresponding to each point
    normals[v1] += n;
    normals[v2] += n;
    normals[v3] += n;
    normals[v4] += n;

    // Add vertices to the triangle vertex list
    quads.push_back(q);
    polygons.push_back(&(quads.back()));
  }
}

void TriangleMesh::AddPolygonTexture(const std::vector<int> textIndices) {
  Assert(textIndices.size() >= 3);

  int v1, v2, v3, v4;

  if (textIndices.size() == 3) {
    v1 = textIndices[0];
    v2 = textIndices[1];
    v3 = textIndices[2];

    // Add vertices to the triangle vertex list
    triangle_textures.push_back(v1);
    triangle_textures.push_back(v2);
    triangle_textures.push_back(v3);

  } else if (textIndices.size() == 4) {
    v1 = textIndices[0];
    v2 = textIndices[1];
    v3 = textIndices[2];
    v4 = textIndices[3];

    // Add vertices to the triangle vertex list
    quad_textures.push_back(v1);
    quad_textures.push_back(v2);
    quad_textures.push_back(v3);
    quad_textures.push_back(v4);
  }
}

void TriangleMesh::ComputeNormal() {
  // We assume at this point all the normals have been added to the normal
  // list, so all we need to do is normalize all the normals
  for (uint32_t i = 0; i < normals.size(); i++) {
    normals[i] = Normalize(normals[i]);
  }
}

Point TriangleMesh::Vertex(int i) const {
  Assert(i >= 0 && i < vertices.size());
  return vertices[i];
}

Vector TriangleMesh::Normal(int i) const {
  Assert(i >= 0 && i < normals.size());
  return normals[i];
}

int TriangleMesh::NumVerts() {
  return vertices.size();
}

BBox TriangleMesh::ObjectBound() const {
  return bbox;
}

void TriangleMesh::Render(const Renderer& r) {
  r.Render(*this);
}

void TriangleMesh::AddMaterial(const Texture& material) {
  materials.push_back(material);
}

void TriangleMesh::LoadMaterialMapping(const std::vector<int> mapping) {
  for (uint32_t i = 0; i < mapping.size(); i++)
    material_mapping.push_back(mapping[i]);
}

}  // namespace ishi
