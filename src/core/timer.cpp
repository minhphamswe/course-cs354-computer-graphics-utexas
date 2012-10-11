/** @file timer.cpp
 * Implements the Timer class for high-resolution timer.
 *
 * @note The implementation is highly O/S / architecture-dependent.
 */

#include <core/timer.h>

#include <ctime>

namespace ishi {

long Resolution() {
#ifdef WIN32
#endif

#ifdef LINUX
  std::timespec ts;
  std::clock_getres(CLOCK_REALTIME, &ts);
  return ts.tv_nsec;
#endif
}

long long unsigned int Time(const Timer& t) {

}

}  // namespace ishi