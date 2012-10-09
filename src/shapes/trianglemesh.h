#ifndef ISHI_SHAPES_TRIANGLEMESH_H_
#define ISHI_SHAPES_TRIANGLEMESH_H_

namespace ishi {

#include <shapes/shape.h>

class TriangleMesh : public Shape {
};

void Render(const TriangleMesh &tm);

}  // namespace ishi

#endif
