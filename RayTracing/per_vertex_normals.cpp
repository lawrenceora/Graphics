void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  Eigen::MatrixXi Adjacency = Eigen::MatrixXi::Zero(V.rows(), F.rows());
  Eigen::RowVector3d curr_normal, a, b, c;

  // Sum all normal components.
  for (int v = 0; v < V.rows(); v++){
    curr_normal = Eigen::RowVector3d::Zero(1, 3);
    for (int f = 0; f < F.rows(); f++){
      if (v == F(f, 0) || v == F(f,1) || v == F(f,2)){
        a = V.row(F(f, 0));
        b = V.row(F(f, 1));
        c = V.row(F(f, 2));
        curr_normal += triangle_area_normal(a,b,c);
      }
    N.row(v) = curr_normal.normalized();
    }
  }
}
