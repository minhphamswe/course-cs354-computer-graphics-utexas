#include <shapes/quad.h>
#include <shapes/trianglemesh.h>

namespace ishi {

Quad::Quad(Transform* o2w, Transform* w2o,
           TriangleMesh *tri_mesh, int pt1, int pt2, int pt3, int pt4,
           int index)
    : Shape(o2w, w2o), tm(tri_mesh), p1(pt1), p2(pt2), p3(pt3), p4(pt4),
      index(index) {
  ComputeNormal();
}

Quad::~Quad() {}

/**
 * Transform the points constituting the triangle to world space first,
 * then compute the bounding box directly to world space.
 */
BBox Quad::ObjectBound() const {
  BBox b = Union(BBox(tm->Vertex(p1), tm->Vertex(p2)),
                 BBox(tm->Vertex(p3), tm->Vertex(p4)));
  return b;
}

void Quad::ComputeNormal() {
  normal = Normalize(Cross(tm->Vertex(p2) - tm->Vertex(p1),
                           tm->Vertex(p3) - tm->Vertex(p2)));
}

void Quad::Render(const Renderer& r) {
  r.Render(*this);
}

Vector Quad::Normal() const {
  return normal;
}

}  // namespace ishi
