#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  
  ////////////////////////////////////////////////////////////////////////////
  
  int idx = 0;
  for (int i=0; i<height; i++) {
    for (int j=0; j<width;j++) {
      if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) { // green position
        bayer[idx] = rgb[3*(i*width+j) + 1];
      } else if (i % 2 == 0 && j % 2 == 1) { // blue position
          bayer[idx] = rgb[3*(i*width+j) + 2];
      } else { // red position
        bayer[idx] = rgb[3*(i*width+j)];
      }
      idx += 1;
    }
  }

  ////////////////////////////////////////////////////////////////////////////
}
