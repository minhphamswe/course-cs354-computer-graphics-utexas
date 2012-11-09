#ifndef ISHI_RENDERING_GLRENDERER_H_
#define ISHI_RENDERING_GLRENDERER_H_

#include <core/renderer.h>

namespace ishi {

class Shape;
class TriangleMesh;

class GLRenderer : public Renderer {
 public:
  GLRenderer();
  ~GLRenderer();

  virtual void Render(const Shape& s) const;
  virtual void Render(const TriangleMesh &tm) const;
};

}  // namespace ishi

#endif
