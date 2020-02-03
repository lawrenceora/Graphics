#include <iostream>
#include <cmath>

void map_to_sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  // We need 2 + num_faces_v * (num_faces_u-1) points in our sphere.
  // Two for the poles, and num_faces_v per intermediate level (num_faces_u - 1)
  int num_points = 2 + num_faces_v * (num_faces_u - 1);
  int point;
  double theta, phi;
  V = Eigen::MatrixXd::Zero(num_points, 3);

  // Initialize poles
  V.row(0) = Eigen::RowVector3d(0, 0, -1);
  V.row(num_points - 1) = Eigen::RowVector3d(0, 0, 1);

  // Initialize intermediate points.
  for (int u = 1; u < num_faces_u; u++){
    theta = M_PI * u / num_faces_u;
    for (int v = 0; v < num_faces_v; v++){
      phi = 2 * M_PI * v / num_faces_v;
      point = num_faces_v * (u-1) + v + 1;
      V(point, 0) =  std::sin(theta) * std::cos(phi);
      V(point, 1) =  std::sin(theta) * std::sin(phi);
      V(point, 2) = -std::cos(theta);
    }
  }

  // Get the four points per face. Then, use the same four points to calculate the normal.
  int num_faces = num_faces_v * num_faces_u;
  int sw, se, nw, ne, face;
  Eigen::RowVector3d sw_v, se_v, nw_v, ne_v, normal;
  F = Eigen::MatrixXi::Zero(num_faces, 4);
  NV = Eigen::MatrixXd::Zero(num_faces, 3);
  NF = Eigen::MatrixXi::Zero(num_faces, 4);
  
  for (int u = 0; u < num_faces_u; u++){
    for (int v = 0; v < num_faces_v; v++){
      sw = 1 + num_faces_v * (u-1) + v;
      se = 1 + num_faces_v * (u-1) + (v+1) % num_faces_v;
      nw = 1 + num_faces_v * u + v;
      ne = 1 + num_faces_v * u + (v+1) % num_faces_v;
      if (u == 0){
        sw = 0;
        se = 0;
      } else if (u == num_faces_u - 1){
        nw = num_points - 1;
        ne = num_points - 1;
      }

      face = num_faces_v*u + v;
      F(face, 0) = sw;
      F(face, 1) = se;
      F(face, 2) = ne;
      F(face, 3) = nw;
      sw_v = V.row(sw);
      se_v = V.row(se);
      nw_v = V.row(ne);
      ne_v = V.row(nw);
      normal = sw_v;
      NV.row(face) = normal;
      NF(face, 0) = face;
      NF(face, 1) = face;
      NF(face, 2) = face;
      NF(face, 3) = face;
    }
  }

  // We need (U+1)x(V+1) points to properly specify the mapping of UxV faces.
  UV = Eigen::MatrixXd::Zero((num_faces_u + 1)*(num_faces_v + 1), 2);
  int coord;
  for (int u = 0; u <= num_faces_u; u++){
    for (int v = 0; v <= num_faces_v; v++){
      coord = (num_faces_v+1)*u + v;
      UV(coord,0) =  v / (double) num_faces_v;
      UV(coord,1) =  u / (double) num_faces_u;
    }
  }

  // Map each face to it's proper coordinates.
  UF = Eigen::MatrixXi::Zero(num_faces, 4);
  for (int u = 0; u < num_faces_u; u++){
    for (int v = 0; v < num_faces_v; v++){
      face = num_faces_v*u + v;
	  sw = (num_faces_v+1)* u    +  v;
      se = (num_faces_v+1)* u    + (v+1);
      nw = (num_faces_v+1)*(u+1) +  v;
      ne = (num_faces_v+1)*(u+1) + (v+1);
	  UF(face, 0) = sw;
	  UF(face, 1) = se;
	  UF(face, 2) = ne;
	  UF(face, 3) = nw;
    }
  }


}
