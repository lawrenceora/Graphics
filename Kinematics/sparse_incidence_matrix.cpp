#include <vector>

void sparse_incidence_matrix(
  const int n,
  const Eigen::MatrixXi & E,
  Eigen::SparseMatrix<double>  & A)
{
  A.resize(E.rows(), n);
  std::vector<Eigen::Triplet<double>> ijv;

  for (int e = 0; e < E.rows(); e++){
    ijv.emplace_back(e, E(e,0), 1);
    ijv.emplace_back(e, E(e,1), -1);
  }

  A.setFromTriplets(ijv.begin(), ijv.end());
}
