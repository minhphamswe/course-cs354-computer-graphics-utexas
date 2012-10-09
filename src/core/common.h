#ifndef CORE_COMMON_H_
#define CORE_COMMON_H_

namespace ishi {

#include <assert.h>
#define Assert assert

#include <stddef.h>
#include <stdint.h>

// Useful constants
#define PI      3.14159265359
#define INV_PI  0.31830988618
#define TWO_PI  6.28318530718
#define INV_180 0.00555555555

#ifdef INFINITY
#undef INFINITY
#endif

#define INFINITY FLT_MAX

///  Return the smaller of two floats
inline float Min(float x, float y);

///  Return the larger of two floats
inline float Max(float x, float y);

/// Return the square of a number
inline float Square(float f);

/// Linearly interpolate between v1 and v2, given position t
inline float Lerp(float t, float v1, float v2);

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


}  // namespace ishi

#endif
