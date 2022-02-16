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
  // int v_row = 0;
  // int uv_row = 0;

  // // 3d vertex on the south pole
  // V.row(v_row) << 0, 0, -radius;
  // v_row += 1;

  // // 2d coordinate on the botton of the texture
  // for (int i = 0; i < num_faces_u + 1; i++) {
  //   UV.row(uv_row) << i / num_faces_u, 0;
  //   uv_row += 1;
  // }

  for (int v = 0; v < num_faces_v + 1; v++) {
    for (int u = 0; u < num_faces_u + 1; u++) {
      double theta = 2 * u * M_PI / num_faces_u;
      double phi = v * M_PI / num_faces_v;
      
      double x = radius * cos(phi) * sin(theta);
      double y = radius * sin(phi) * sin(theta);
      double z = radius * cos(theta);

      V.row(row) << x, y, z;
      UV.row(row) << static_cast<double>(u) / num_faces_u, static_cast<double>(v) / num_faces_v;
      NV.row(row) << x, y, z;
      row += 1;
    }

    // // 2d coordinate on the right edge of the texture
    // UV.row(uv_row) <<  1, v / num_faces_v;
    // uv_row += 1;
  }

  // // 3d vertex on the north pole
  // V.row(v_row) << 0, 0, radius;
  // v_row += 1;

  // // 2d coordinate on the top of the texture
  // for (int i = 0; i < num_faces_u + 1; i++) {
  //   UV.row(uv_row) << i / num_faces_u, 1;
  //   uv_row += 1;
  // }

  // NV = V.normalized();

  // calculate F, UF, NF
  row = 0;

  // int f_row = 0;
  // int uf_row = 0;
  // bool botton = false;
  // bool top = false;
  // bool right = false;

  for (int v = 0; v < num_faces_v; v++) {
    for (int u = 0; u < num_faces_u; u++) {
      int botton_left = v * (num_faces_u + 1) + u;
      int botton_right = v * (num_faces_u + 1) + u + 1;
      int top_left = (v + 1) * (num_faces_u + 1) + u;
      int top_right = (v + 1) * (num_faces_u + 1) + u + 1;

      // if (v == 0) {
      //   botton_left = botton_right = 0;
      // }
      // if (v == num_faces_v - 1) {
      //   top_left = top_right = V.rows() - 1;
      // }
      // if (u == num_faces_u - 1) {
      //   botton_right -= u;
      //   top_right -= u;
      // }

      F.row(row) << botton_left, botton_right, top_right, top_left;
      UF.row(row) << botton_left, botton_right, top_right, top_left;
      NF.row(row) << botton_left, botton_right, top_right, top_left;
      row += 1;

      // botton_left = v * (num_faces_u + 1) + u;
      // botton_right = v * (num_faces_u + 1) + u + 1;
      // top_left = (v + 1) * (num_faces_u + 1) + u;
      // top_right = (v + 1) * (num_faces_u + 1) + u + 1;

      // UF.row(uf_row) << botton_left, botton_right, top_right, top_left;
      // uf_row += 1;
    }
  }

  // NF = F;

  ////////////////////////////////////////////////////////////////////////////
}
