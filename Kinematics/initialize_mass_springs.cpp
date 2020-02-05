#include <vector>

bool initialize_mass_springs(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double>  & M,
  Eigen::SparseMatrix<double>  & A,
  Eigen::SparseMatrix<double>  & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
{
  std::vector<Eigen::Triplet<double>> ijv;

  // Calculate Edge Lengths. It is not sparse.
  r.resize(E.rows(), 1);
  for (int i = 0; i < E.rows(); i++){
    r(i, 0) = (V.row(E(i,0)) - V.row(E(i,1))).norm();
  }

  // Calculate Mass Matrix.
  M.resize(V.rows(), V.rows());
  for (int i = 0; i < V.rows(); i++){
    ijv.emplace_back(i, i, m(i));
  }
  M.setFromTriplets(ijv.begin(), ijv.end());
  ijv.clear();

  // Calculate Signed Incidence Matrix:
  sparse_incidence_matrix(V.rows(), E, A);

  // Calculate Pinned Vertices Matrix:
  C.resize(b.rows(), V.rows());
  for (int i = 0; i < b.rows(); i++){
    ijv.emplace_back(i, b(i), 1);
  }
  C.setFromTriplets(ijv.begin(), ijv.end());

  // Calculate prefactorization:
  Eigen::SparseMatrix<double> Q;
  Q.resize(V.rows(), V.rows());
  Q = k*A.transpose()*A + (1/(delta_t*delta_t))*M + 1e10*C.transpose()*C;
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
} 

