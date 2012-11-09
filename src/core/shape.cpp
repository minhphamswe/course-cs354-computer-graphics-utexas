#include <core/shape.h>
#include <core/renderer.h>

// #include <stdio.h>

namespace ishi {

int Shape::nextShapeID = 1;

Shape::Shape(const Transform* o2w, const Transform* w2o)
    : ObjectToWorld(o2w), WorldToObject(w2o), shapeID(nextShapeID++) { }

Shape::~Shape() { }

BBox Shape::WorldBound() const {
  return (*ObjectToWorld)(ObjectBound());
}

}  // namespace ishi
