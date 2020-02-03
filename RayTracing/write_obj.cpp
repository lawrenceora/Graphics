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
  std::ofstream f(filename.c_str());
  if (f.bad()){
    fprintf(stderr, "File cannot be opened for writing");
    return false;
  }

  int rows, poly;

  f << "# Vertex Positions\n";
  rows = V.rows();
  for (int i = 0; i < rows; i++){
    f << "v ";
    for (int j = 0; j < 3; j++){
        f << V(i,j) << " ";
    }
    f << "\n";
  }
 
  f << "# UV Coordinates\n";
  rows = UV.rows();
  for (int i = 0; i < rows; i++){
    f << "vt ";
    for (int j = 0; j < 2; j++){
        f << UV(i,j) << " ";
    }
    f << "\n";
  }

  f << "# Normal Vectors\n";
  rows = NV.rows();
  for (int i = 0; i < rows; i++){
    f << "vn ";
    for (int j = 0; j < 3; j++){
        f << NV(i,j) << " ";
    }
    f << "\n";
  }

  f << "# Face elements\n";
  rows = F.rows();
  poly = F.cols();
  for (int i = 0; i < rows; i++){
    f << "f ";
    for (int j = 0; j < poly; j++){
        f << F(i,j) + 1 << "/" << UF(i,j) + 1 << "/" << NF(i,j) + 1 << " ";
    }
    f << "\n";
  }

  return true;
}
