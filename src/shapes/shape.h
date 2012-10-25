#ifndef ISHI_SHAPES_SHAPE_H_
#define ISHI_SHAPES_SHAPE_H_

#include <core/transform.h>
#include <core/bbox.h>

namespace ishi {

/**
 * The Shape class is a container for geometric information and geometric
 * methods (and those only).
 */
class Shape {
 public:
  Transform *ObjectToWorld;
  Transform *WorldToObject;

 public:
  Shape(const Transform *o2w, const Transform *w2o);
  virtual ~Shape();

  /// Return the bounding box of the shape in object space
  /// @note This method must be overridden by derived classes
  virtual BBox ObjectBound() const = 0;

  /// Return the bounding box of the shape, in world space
  /// @note A default implementation is provided, but shapes should override
  /// this method if it can compute a tighter bounding box
  virtual BBox WorldBound() const;
};

}  // namespace ishi

#endif
