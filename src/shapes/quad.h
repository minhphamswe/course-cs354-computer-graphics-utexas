#ifndef ISHI_SHAPES_QUAD_H_
#define ISHI_SHAPES_QUAD_H_

#include <core/point.h>
#include <core/shape.h>
#include <core/vector.h>

#include <rendering/GLRenderer.h>

#include <shapes/trianglemesh.h>

namespace ishi {

class Quad : public Shape {
 private:
  Transform *ObjectToWorld;
  int p1, p2, p3, p4;
  Vector normal;
  TriangleMesh *tm;
  int index;

 public:
  Quad(Transform* o2w, Transform* w2o,
       TriangleMesh *tri_mesh, int pt1, int pt2, int pt3, int pt4, int index);

  virtual ~Quad();

  virtual BBox ObjectBound() const;

  void ComputeNormal();

  Vector Normal() const;

  virtual void Render(const Renderer& r);

  friend class GLRenderer;
};

}  // namespace ishi

#endif
