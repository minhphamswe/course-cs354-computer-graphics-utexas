#ifndef ISHI_SHAPES_SHAPE_H_
#define ISHI_SHAPES_SHAPE_H_

namespace ishi {

#include <shapes/trianglemesh.h>

class Shape {
 private:
  TriangleMesh tm;

 public:
  virtual ~Shape();

  /// Render the shape
  virtual void Render() const;

  /// Return the mesh underlying the shape
  virtual TriangleMesh& Mesh() const;
};

}  // namespace ishi

#endif
