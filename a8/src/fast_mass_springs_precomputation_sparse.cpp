#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>

bool fast_mass_springs_precomputation_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double> & M,
  Eigen::SparseMatrix<double> & A,
  Eigen::SparseMatrix<double> & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
  
  r.resize(E.rows());
  for (int i=0; i<E.rows(); i++) {
    r[i] = (V.row(E(i, 0)) - V.row(E(i, 1))).norm();
  }

  M.resize(V.rows(), V.rows());
  std::vector<Eigen::Triplet<double> > ijv;
  for (int i=0; i<V.rows(); i++) {
    ijv.emplace_back(i, i, m[i]);
  }
  M.setFromTriplets(ijv.begin(), ijv.end());
  ijv.clear();

  signed_incidence_matrix_sparse(V.rows(), E, A);

  C.resize(b.size(), V.rows());
  for (int i=0; i<b.size(); i++) {
    ijv.emplace_back(i, b[i], 1);
  }
  C.setFromTriplets(ijv.begin(), ijv.end());
  ijv.clear();

  Eigen::SparseMatrix<double> Q(V.rows(), V.rows());
  double w = 1e10;
  Q = k * A.transpose() * A + M / std::pow(delta_t, 2) + w * C.transpose() * C;

  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
