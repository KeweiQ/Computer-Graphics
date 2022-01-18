#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  
  if (num_channels == 3) {
    for (int i=0; i<width; i++) {
      for (int j=0; j<height; j++) {
        rotated[3 * (i*height + j)] = input[3 * ((j+1)*width - i - 1)];
        rotated[3 * (i*height + j) + 1] = input[3 * ((j+1)*width - i - 1) + 1];
        rotated[3 * (i*height + j) + 2] = input[3 * ((j+1)*width - i - 1) + 2];
      }
    }

  } else if (num_channels == 1) {
    for (int i=0; i<width; i++) {
      for (int j=0; j<height; j++) {
        rotated[i*height + j] = input[(j+1)*width - i - 1];
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////
}
