#include <igl/matlab_format.h>

void mass_springs_step(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXi & b,
  const double delta_t,
  const Eigen::MatrixXd & fext,
  const Eigen::VectorXd & r,
  const Eigen::SparseMatrix<double>  & M,
  const Eigen::SparseMatrix<double>  & A,
  const Eigen::SparseMatrix<double>  & C,
  const Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization,
  const Eigen::MatrixXd & Uprev,
  const Eigen::MatrixXd & Ucur,
  Eigen::MatrixXd & Unext)
{
  // Initialize space for b.
  Eigen::MatrixXd B;
  
  // Calculate Urest, the initial positions of all rest vertices.
  Eigen::MatrixXd Urest = Eigen::MatrixXd::Zero(b.size(), 3);
  for (int i = 0; i < b.size(); i++){
    Urest.row(i) = V.row(b(i));
  }
  
  // Initialize y. y is independent of D and Unext. The last term is the penalty.
  Eigen::MatrixXd y = M * (2*Ucur - Uprev) / (delta_t*delta_t) + fext + 1e10*C.transpose()*Urest;
  
  // Initialize matrix D where D.row(k) is the solution to the minimization problem in Liu et al.
  Eigen::MatrixXd D = Eigen::MatrixXd::Zero(E.rows(), 3);
  
  // Set Unext to Ucur for the first iteration.
  Unext = Ucur;
  
  // Perform local-global iterative algorithm.
  for (int iter = 0; iter < 50; iter++){
    // Find optimal values of D for current value of Unext
    for (int i = 0; i < E.rows(); i++){
      D.row(i) = r(i) * (Unext.row(E(i, 0)) - Unext.row(E(i,1))).normalized();
    }
    
    // Solve for B
    B = k*A.transpose()*D + y;
    
    // Update Unext as the derivative of the energy function.
    Unext = prefactorization.solve(B);
  }
}
