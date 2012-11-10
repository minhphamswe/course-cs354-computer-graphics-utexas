#ifndef ISHI_SHAPES_TRIANGLE_H_
#define ISHI_SHAPES_TRIANGLE_H_

#include <core/point.h>
#include <core/shape.h>
#include <core/vector.h>

#include <shapes/trianglemesh.h>

#include <rendering/GLRenderer.h>

namespace ishi {

class Triangle : public Shape {
 private:
  Transform *ObjectToWorld;
  int p1, p2, p3;
  Vector normal;
  TriangleMesh *tm;
  int index;

 public:
  Triangle(Transform* o2w, Transform* w2o,
           TriangleMesh *tri_mesh, int pt1, int pt2, int pt3, int index);

  virtual ~Triangle();

  virtual BBox ObjectBound() const;

  void ComputeNormal();

  Vector Normal() const;

  virtual void Render(const Renderer& r);

  friend class GLRenderer;
};

}  // namespace ishi

#endif
