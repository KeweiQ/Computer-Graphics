#include "rgb_to_hsv.h"
#include <algorithm>
#include <cmath>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  // Formula used from: https://en.wikipedia.org/wiki/HSL_and_HSV
  
  const double cmax = std::max({r, g, b});
  const double cmin = std::min({r, g, b});
  const double delta = cmax - cmin;
  const double partial = delta == 0 ? 0 : (g - b) / delta;

  if (cmax == 0) {
    h = 0;
  } else if (cmax == r) {
    h = (fmod(partial, 6) < 0) ? 60 * (fmod(partial, 6) + 6) : 60 * fmod(partial, 6);
  } else if (cmax == g) {
    h = 60 * ((b - r) / delta + 2);
  } else {
    h = 60 * ((r - g) / delta + 4);
  }

  s = (cmax == 0) ? 0 : delta / cmax;
  v = cmax;
  
  ////////////////////////////////////////////////////////////////////////////
}
