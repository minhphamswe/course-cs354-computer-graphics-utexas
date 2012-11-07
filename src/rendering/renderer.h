#ifndef ISHI_RENDERING_RENDERER_H_
#define ISHI_RENDERING_RENDERER_H_

#include <stdio.h>

namespace ishi {

class Shape;

class Renderer {
 public:
  Renderer() {}

  virtual void visit(const Shape &s);
};

}  // namespace ishi

#endif
