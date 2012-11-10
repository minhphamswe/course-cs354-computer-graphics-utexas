#include <shapes/triangle.h>
#include <shapes/trianglemesh.h>

namespace ishi {

Triangle::Triangle(Transform* o2w, Transform* w2o,
                   TriangleMesh *tri_mesh, int pt1, int pt2, int pt3,
                   int index)
    : Shape(o2w, w2o), tm(tri_mesh), p1(pt1), p2(pt2), p3(pt3),
      index(index) {
  ComputeNormal();
}

Triangle::~Triangle() {}

/**
 * Transform the points constituting the triangle to world space first,
 * then compute the bounding box directly to world space.
 */
BBox Triangle::ObjectBound() const {
  BBox b = Union(BBox(tm->Vertex(p1), tm->Vertex(p2)), tm->Vertex(p3));
  return b;
}

void Triangle::ComputeNormal() {
  normal = Normalize(Cross(tm->Vertex(p2) - tm->Vertex(p1),
                           tm->Vertex(p3) - tm->Vertex(p2)));
}

void Triangle::Render(const Renderer& r) {
  r.Render(*this);
}

Vector Triangle::Normal() const {
  return normal;
}




}  // namespace ishi
