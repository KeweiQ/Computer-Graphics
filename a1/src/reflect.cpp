#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  
  ////////////////////////////////////////////////////////////////////////////
  
  if (num_channels == 3) {
    for (int i=0; i<height; i++) {
      for (int j=0; j<width; j++) {
        reflected[3 * (i*width + j)] = input[3 * ((i+1)*width - j - 1)];
        reflected[3 * (i*width + j) + 1] = input[3 * ((i+1)*width - j - 1) + 1];
        reflected[3 * (i*width + j) + 2] = input[3 * ((i+1)*width - j - 1) + 2];
      }
    }

  } else if (num_channels == 1) {
    for (int i=0; i<height; i++) {
      for (int j=0; j<width; j++) {
        reflected[i*width + j] = input[(i+1)*width - j - 1];
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////
}
