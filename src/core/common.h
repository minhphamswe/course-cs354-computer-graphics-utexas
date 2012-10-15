#ifndef ISHI_CORE_COMMON_H_
#define ISHI_CORE_COMMON_H_

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <float.h>
#include <cmath>

namespace ishi {

#define Assert assert

// Useful constants
#define PI      3.14159265359
#define INV_PI  0.31830988618
#define TWO_PI  6.28318530718
#define INV_180 0.00555555556

#ifndef INFINITY
#define INFINITY FLT_MAX
#endif

///  Return the smaller of two floats
inline float Min(float x, float y);

///  Return the larger of two floats
inline float Max(float x, float y);

/// Return the square of a number
inline float Square(float f);

/// Linearly interpolate between v1 and v2, given position t
inline float Lerp(float t, float v1, float v2);

/** Convert degree to radian. */
inline float Radian(float deg);

/** Convert radian to degree. */
inline float Degree(float rad);

inline float Min(float x, float y) {
  return (x < y) ? x : y;
}

inline float Max(float x, float y) {
  return (x > y) ? x : y;
}

inline float Square(float f) {
  return f * f;
}

inline float Lerp(float t, float v1, float v2) {
  return (1.0f - t) * v1 + t * v2;
}

inline float Radian(float deg) {
  return deg * INV_180 * PI;
}

inline float Degree(float rad) {
  return rad * INV_PI * 180;
}


}  // namespace ishi

#endif
