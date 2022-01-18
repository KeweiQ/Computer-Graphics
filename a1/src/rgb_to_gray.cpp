#include "rgb_to_gray.h"
#include <iostream>

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  
  ////////////////////////////////////////////////////////////////////////////
  
  int j = 0;
  for (int i=0; i<height*width; i++) {
    const double r = (double)rgb[i*3] / 255;
    const double g = (double)rgb[i*3+1] / 255;
    const double b = (double)rgb[i*3+2] / 255;
    const double grayTemp = 0.2126 * r + 0.7152 * g + 0.0722 * b;
    const double grayscale = grayTemp * 255;
    gray[j] = (unsigned char)grayscale;
    j += 1;
  }

  ////////////////////////////////////////////////////////////////////////////
}


