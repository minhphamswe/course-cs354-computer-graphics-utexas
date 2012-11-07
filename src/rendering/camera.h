#ifndef ISHI_RENDERING_CAMERA_H_
#define ISHI_RENDERING_CAMERA_H_

#include <core/point.h>
#include <core/vector.h>
#include <shapes/shape.h>

namespace ishi {

class Camera {
private:
  Point l;          // Location of the camera
  Vector d;         // Direction the camera is pointing
  Vector u;         // Direction the camera considers up

  Transform *CameraToWorld;       // Camera-to-World transformation
  Transform *WorldToCamera;       // World-to-Camera transformation

public:
  //================== Individual Camera methods =============================
  /// Initialize a camera at the origin, looking towards -Z, up towards +Y
  Camera();

  /// Initialize a camera 
  Camera(const Point &loc, const Vector &dir, const Vector &up);

  /// Render objects in the scene from this camera's perspective
  void Render(const Shape &s);

  /// Cast a ray from this camera in the direction it is pointing
  void CastRay();


  //================== Camera System methods =================================
  /// Return the camera with the assigned id
  static Camera GetCamera(int id);

  static AddCamera(const Camera &cam);
};

}

#endif