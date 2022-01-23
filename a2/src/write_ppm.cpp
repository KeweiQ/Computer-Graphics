#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <algorithm>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////

  unsigned char maxval = *std::max_element(data.begin(), data.end());

  std::ofstream pfile;
  pfile.open(filename);
  if (!pfile) {
    return false;
  }

  if (num_channels == 3) {
    pfile << "P3" << std::endl << width << ' ' << height << std::endl << 255 << std::endl;
    for (int i=0; i<height*width; i++) {
      pfile << +data[i*3] << ' ' << +data[i*3+1] << ' ' << +data[i*3+2] << std::endl;
    }

  } else {
    pfile << "P2" << std::endl << width << ' ' << height << std::endl << 255 << std::endl;
    for (int i=0; i<height*width; i++) {
      pfile << +data[i] << std::endl;
    }
  }

  pfile.close();
  return true;
  
  ////////////////////////////////////////////////////////////////////////////
}
