#include <iostream>
#include <cmath>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  std::vector<std::vector<int>> VF(0, std::vector<int>(0,0));
  vertex_triangle_adjacency(F, V.rows(), VF);
  int corner;
  Eigen::RowVector3d a, b, c, face_normal, corner_normal, adj_normal;

  for (int f = 0; f < F.rows(); f++){
    a = V.row(F(f, 0));
    b = V.row(F(f, 1));
    c = V.row(F(f, 2));
    face_normal = triangle_area_normal(a, b, c);

    for (int i = 0; i < 3; i++){
      corner = F(f,i);
      corner_normal = Eigen::RowVector3d(0,0,0);
      for (int j = 0; j < VF[corner].size(); j++){
        a = V.row(F(VF[corner][j], 0));
        b = V.row(F(VF[corner][j], 1));
        c = V.row(F(VF[corner][j], 2));
        adj_normal = triangle_area_normal(a,b,c);
        if (face_normal.dot(adj_normal)/(face_normal.norm() * adj_normal.norm()) >  std::cos(M_PI * corner_threshold / 180 )){
          corner_normal += adj_normal;
        }
      N.row(3*f + i) = corner_normal.normalized();
      }
    }
  }
}
