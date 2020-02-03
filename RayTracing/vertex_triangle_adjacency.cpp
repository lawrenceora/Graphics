void vertex_triangle_adjacency(
  const Eigen::MatrixXi & F,
  const int num_vertices,
  std::vector<std::vector<int> > & VF)
{
  VF.resize(num_vertices);
  int a, b, c;

  for (int v = 0; v < num_vertices; v++){
    for (int f = 0; f < F.rows(); f++){
      a = F(f, 0);
      b = F(f, 1);
      c = F(f, 2);
      VF[a].push_back(f);
      if (a != b){
        VF[b].push_back(f);
      }
      if (c != a && c != b){
        VF[c].push_back(f);
      }
    }
  }
}

