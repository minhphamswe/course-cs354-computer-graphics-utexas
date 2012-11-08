#include <shapes/trianglemesh.h>
#include <core/common.h>
#include <core/point.h>
#include <core/vector.h>
#include <core/transform.h>

#include <vector>

namespace ishi {

TriangleMesh::TriangleMesh()
    : o2w(), w2o(), bbox(), ObjectToWorld(&o2w), WorldToObject(&w2o),
      Shape(ObjectToWorld, WorldToObject) {}

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
//   printf("Address before: %x\n", &o2w);
  o2w = Translate(Point() - center);
  w2o = Inverse(o2w);
//   printf("Address after: %x\n", &o2w);
}

void TriangleMesh::AddPolygon(const std::vector<int> vertIndices) {
//   printf("Adding polygon ...\n");
  Assert(vertIndices.size() >= 3);

  int v1, v2, v3, v4;

  if (vertIndices.size() == 3) {
      v1 = vertIndices[0];
      v2 = vertIndices[1];
      v3 = vertIndices[2];

      // Get the points pointed to by the indices
      Point *p1 = &vertices[v1];
      Point *p2 = &vertices[v2];
      Point *p3 = &vertices[v3];

      // Compute the normalized normal of the triangle
      Vector n = Normalize(Cross((*p2 - *p1), (*p3 - *p2)));

      // Add the normal to the normal list corresponding to each point
      normals[v1] += n;
      normals[v2] += n;
      normals[v3] += n;

      // Add vertices to the triangle vertex list
      triangles.push_back(p1);
      triangles.push_back(p2);
      triangles.push_back(p3);
  } else if (vertIndices.size() == 4) {
      v1 = vertIndices[0];
      v2 = vertIndices[1];
      v3 = vertIndices[2];
      v4 = vertIndices[3];

      // Get the points pointed to by the indices
      Point *p1 = &vertices[v1];
      Point *p2 = &vertices[v2];
      Point *p3 = &vertices[v3];
      Point *p4 = &vertices[v4];

      // Compute the normalized normal of the triangle
      Vector n = Normalize(Cross((*p2 - *p1), (*p3 - *p2)));

      // Add the normal to the normal list corresponding to each point
      normals[v1] += n;
      normals[v2] += n;
      normals[v3] += n;
      normals[v4] += n;

      // Add vertices to the triangle vertex list
      quads.push_back(p1);
      quads.push_back(p2);
      quads.push_back(p3);
      quads.push_back(p4);
  }
}

void TriangleMesh::ComputeNormal() {
//   printf("Computing Normal ...");
  // We assume at this point all the normals have been added to the normal
  // list, so all we need to do is normalize all the normals
  for (int i = 0; i < normals.size(); i++) {
    normals[i] = Normalize(normals[i]);
  }

  // TODO: remove debug statements
//   Point *p;
//   for (int i = 0; i < triangles.size(); i++) {
//     p = triangles[i];
//     printf("Vertex %d: (%f %f %f)\n", i, p->x, p->y, p->z);
//   }
}

Point TriangleMesh::Vertex(int i) {
  return vertices[i];
}

Vector TriangleMesh::Normal(int i) {
  return normals[i];
}

int TriangleMesh::NumVerts(int i) {
  return vertices.size();
}

BBox TriangleMesh::ObjectBound() const {
  return bbox;
}

void TriangleMesh::accept(const Renderer& r) {
  r.Render(*this);
}

}  // namespace ishi
