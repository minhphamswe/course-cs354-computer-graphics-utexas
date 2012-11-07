#ifndef ISHI_RENDERING_GLRENDERER_H_
#define ISHI_RENDERING_GLRENDERER_H_

#include <shapes/shape.h>
// #include <shapes/trianglemesh.h>
#include <rendering/renderer.h>

namespace ishi {

class TriangleMesh;

class GLRenderer : public Renderer {

  virtual void visit(TriangleMesh &tm) {};
};

}  // namespace ishi

#endif