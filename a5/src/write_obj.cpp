#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  
  std::ofstream pfile(filename);
  if (!pfile) {
    return false;
  }

  // list of geometric vertices, with (x, y, z) coordinates
  for (int i = 0; i < V.rows(); i++) {
    pfile << "v " << V(i, 0) << " " << V(i, 1) << " " << V(i, 2) << std::endl;
  }

  // list of vertex normals in (x,y,z) form, normals might not be unit vectors
  for (int i = 0; i < NV.rows(); i++) {
    pfile << "vn " << NV(i, 0) << " " << NV(i, 1) << " " << NV(i, 2) << std::endl;
  }

  // list of texture coordinates, in (u, v) coordinates, these will vary between 0 and 1
  for (int i = 0; i < UV.rows(); i++) {
    pfile << "vt " << UV(i, 0) << " " << UV(i, 1) << std::endl;
  }

  // list of all indices, in vertex index/vertex texture coordinate index/vertex normal index form
  for (int i = 0; i < F.rows(); ++i) { // in C++ indices start at 0, but in a .obj file indices start at 1
    pfile << "f ";
    for (int j = 0; j < F.cols(); j++) {
      pfile << F(i, j) << "/" << UF(i, j) << "/" << NF(i, j) << " ";
    }
    pfile << std::endl;
  }

  pfile.close();
  return true;

  ////////////////////////////////////////////////////////////////////////////
}
