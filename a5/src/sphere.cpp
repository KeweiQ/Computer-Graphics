#include "sphere.h"
#include <iostream>
#include <math.h>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  
  const double num_faces = num_faces_u * num_faces_v;
  const double num_vertices = (num_faces_u + 1) * (num_faces_v + 1);
  const double radius = 1;

  V.resize(num_vertices, 3);
  F.resize(num_faces, 4);
  UV.resize(num_vertices, 2);
  UF.resize(num_faces, 4);
  NV.resize(num_vertices, 3);
  NF.resize(num_faces, 4);

  // calculate V, UV, NV
  int row = 0;

  for (int u = 0; u < num_faces_u+ 1; u++) {
    for (int v = 0; v < num_faces_v + 1; v++) {
      double theta = 2 * static_cast<double>(u) * M_PI / num_faces_u;
      double phi = static_cast<double>(v) * M_PI / num_faces_v;
      
      double x = radius * cos(theta) * sin(phi);
      double z = radius * sin(theta) * sin(phi);
      double y = -radius * cos(phi);

      V.row(row) << x, y, z;
      UV.row(row) << 1 - static_cast<double>(u) / num_faces_u, static_cast<double>(v) / num_faces_v;
      NV.row(row) << x, y, z;
      row += 1;
    }
  }

  // calculate F, UF, NF
  row = 0;

  for (int u = 0; u < num_faces_u; u++) {
    for (int v = 0; v < num_faces_v; v++) {
      int botton_left = u * (num_faces_v + 1) + v;
      int botton_right = u * (num_faces_v + 1) + v + 1;
      int top_left = (u + 1) * (num_faces_v + 1) + v;
      int top_right = (u + 1) * (num_faces_v + 1) + v + 1;

      F.row(row) << botton_left, top_left, top_right, botton_right;
      UF.row(row) << botton_left, top_left, top_right, botton_right;
      NF.row(row) << botton_left, top_left, top_right, botton_right;
      row += 1;
    }
  }

  ////////////////////////////////////////////////////////////////////////////
}
