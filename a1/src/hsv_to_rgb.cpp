#include "hsv_to_rgb.h"
#include <cmath>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  ////////////////////////////////////////////////////////////////////////////
  // Formula used from: https://en.wikipedia.org/wiki/HSL_and_HSV
  
  const double c = v * s;
  const double mod = fmod(h / 60, 2) < 0 ?  fmod(h / 60, 2) + 2 : fmod(h / 60, 2);
  const double x = c * (1 - fabs(mod - 1));
  const double m = v - c;

  if (h >= 0 && h < 60) {
    r = c + m;
    g = x + m;
    b = 0 + m;
  } else if (h >= 60 && h < 120) {
    r = x + m;
    g = c + m;
    b = 0 + m;
  } else if (h >= 120 && h < 180) {
    r = 0 + m;
    g = c + m;
    b = x + m;
  } else if (h >= 180 && h < 240) {
    r = 0 + m;
    g = x + m;
    b = c + m;
  } else if (h >= 240 && h < 300) {
    r = x + m;
    g = 0 + m;
    b = c + m;
  } else {
    r = c + m;
    g = 0 + m;
    b = x + m;
  }

  ////////////////////////////////////////////////////////////////////////////
}
