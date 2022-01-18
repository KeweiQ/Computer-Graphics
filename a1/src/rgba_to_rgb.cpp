#include "rgba_to_rgb.h"
#include <iostream>

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);

  ////////////////////////////////////////////////////////////////////////////

  int j = 0;
  for (int i=0; i<height*width*4; i++) {
    if ((i+1) % 4 != 0) {
      rgb[j] = rgba[i];
      j += 1;
    }
  }
  
  ////////////////////////////////////////////////////////////////////////////
}
