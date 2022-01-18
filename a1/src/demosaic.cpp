#include "demosaic.h"

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);

  ////////////////////////////////////////////////////////////////////////////
  
  for (int i=0; i<height; i++) {
    for (int j=0; j<width;j++) {
      // calculate indeces
      const int left = j - 1;
      const int right = j + 1;
      const int top = i - 1;
      const int bottom = i + 1;
      double count = 0;
      double sum = 0;

      if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) { // green position
        // get red channel
        if (i % 2 == 1) { // left and right
          if (left >= 0) {
            count += 1;
            sum += +bayer[i*width+left];
          }
          if (right < width) {
            count += 1;
            sum += +bayer[i*width+right];
          }
        } else { // top and bottom
          if (top >= 0) {
            count += 1;
            sum += +bayer[top*width+j];
          }
          if (bottom < height) {
            count += 1;
            sum += +bayer[bottom*width+j];
          }
        }
        rgb[3*(i*width+j)] = (unsigned char)(sum / count);
        sum = 0;
        count = 0;

        // get green channel
        rgb[3*(i*width+j) + 1] = +bayer[i*width+j];

        // get blue channel
        if (i % 2 == 0) { // left and right
          if (left >= 0) {
            count += 1;
            sum += +bayer[i*width+left];
          }
          if (right < width) {
            count += 1;
            sum += +bayer[i*width+right];
          }
        } else { // top and bottom
          if (top >= 0) {
            count += 1;
            sum += +bayer[top*width+j];
          }
          if (bottom < height) {
            count += 1;
            sum += +bayer[bottom*width+j];
          }
        }
        rgb[3*(i*width+j) + 2] = (unsigned char)(sum / count);
        sum = 0;
        count = 0;

      } else if (i % 2 == 0 && j % 2 == 1) { // blue position
        // get red channel (four cornels)
        if (left >= 0) {
          if (top >= 0) {
            count += 1;
            sum += +bayer[top*width+left];
          }
          if (bottom < height) {
            count += 1;
            sum += +bayer[bottom*width+left];
          }
        }
        if (right < width) {
          if (top >= 0) {
            count += 1;
            sum += +bayer[top*width+right];
          }
          if (bottom < height) {
            count += 1;
            sum += +bayer[bottom*width+right];
          }
        }
        rgb[3*(i*width+j)] = (unsigned char)(sum / count);
        sum = 0;
        count = 0;
        
        // get green channel
        if (left >= 0) {
          count += 1;
          sum += +bayer[i*width+left];
        }
        if (right < width) {
          count += 1;
          sum += +bayer[i*width+right];
        }
        if (top >= 0) {
          count += 1;
          sum += +bayer[top*width+j];
        }
        if (bottom < height) {
          count += 1;
          sum += +bayer[bottom*width+j];
        }
        rgb[3*(i*width+j) + 1] = (unsigned char)(sum / count);
        sum = 0;
        count = 0;

        // get blue channel
        rgb[3*(i*width+j) + 2] = +bayer[i*width+j];

      } else { // red position
        // get red channel
        rgb[3*(i*width+j)] = +bayer[i*width+j];

        // get green channel
        if (left >= 0) {
          count += 1;
          sum += +bayer[i*width+left];
        }
        if (right < width) {
          count += 1;
          sum += +bayer[i*width+right];
        }
        if (top >= 0) {
          count += 1;
          sum += +bayer[top*width+j];
        }
        if (bottom < height) {
          count += 1;
          sum += +bayer[bottom*width+j];
        }
        rgb[3*(i*width+j) + 1] = (unsigned char)(sum / count);
        sum = 0;
        count = 0;

        // get blue channel
        if (left >= 0) {
          if (top >= 0) {
            count += 1;
            sum += +bayer[top*width+left];
          }
          if (bottom < height) {
            count += 1;
            sum += +bayer[bottom*width+left];
          }
        }
        if (right < width) {
          if (top >= 0) {
            count += 1;
            sum += +bayer[top*width+right];
          }
          if (bottom < height) {
            count += 1;
            sum += +bayer[bottom*width+right];
          }
        }
        rgb[3*(i*width+j) + 2] = (unsigned char)(sum / count);
        sum = 0;
        count = 0;
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////
}
