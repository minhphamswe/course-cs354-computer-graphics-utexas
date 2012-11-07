#ifndef ISHI_RENDERING_GLRENDERER_H_
#define ISHI_RENDERING_GLRENDERER_H_

#include <rendering/renderer.h>

namespace ishi {

class Shape;
class TriangleMesh;

class GLRenderer : public Renderer {
 public:
  GLRenderer();
  ~GLRenderer();

  virtual void Render(const Shape& s);
  virtual void Render(const TriangleMesh &tm);
};

}  // namespace ishi

#endif
