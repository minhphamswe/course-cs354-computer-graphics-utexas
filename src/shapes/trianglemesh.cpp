#include <shapes/trianglemesh.h>
#include <core/common.h>
#include <core/point.h>
#include <core/vector.h>
#include <core/transform.h>

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
  printf("Address before: %x\n", &o2w);
  o2w = Translate(Point() - center);
  w2o = Inverse(o2w);
  printf("Address after: %x\n", &o2w);
}

void TriangleMesh::AddPolygon(int v1, int v2, int v3) {
//   printf("Adding polygon ...\n");
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

  // TODO: remove debug statements
//   printf("Geometry Polygon Indices: (%d, %d, %d)\n", v1, v2, v3);
//   printf("Point 1 has coordinates: (%f %f %f)\n", p1->x, p1->y, p1->z);
//   printf("Point 2 has coordinates: (%f %f %f)\n", p2.x, p2.y, p2.z);
//   printf("Point 3 has coordinates: (%f %f %f)\n", p3.x, p3.y, p3.z);
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

void TriangleMesh::accept(Renderer& r) {
  r.Render(*this);
}

}  // namespace ishi
