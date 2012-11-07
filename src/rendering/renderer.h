#ifndef ISHI_RENDERING_RENDERER_H_
#define ISHI_RENDERING_RENDERER_H_

#include <stdio.h>

namespace ishi {

class Shape;
class TriangleMesh;

class Renderer {
 public:
  Renderer();
  virtual ~Renderer();

  virtual void visit(const Shape &s) = 0;
  virtual void visit(const TriangleMesh &s) = 0;
};

}  // namespace ishi

#endif
