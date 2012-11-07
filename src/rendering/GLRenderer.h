#ifndef ISHI_RENDERING_GLRENDERER_H_
#define ISHI_RENDERING_GLRENDERER_H_

#include <rendering/renderer.h>

namespace ishi {

class TriangleMesh;

class GLRenderer : public Renderer {
 public:
  GLRenderer();
  ~GLRenderer();

  virtual void visit(const Shape& s);
  virtual void visit(const TriangleMesh &tm);
};

}  // namespace ishi

#endif