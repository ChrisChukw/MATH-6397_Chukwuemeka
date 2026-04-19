#include "my_matrix.hh"
#include "proto_blas_lapack.hh"


// operator* specializations
// C = A * B. We use BLAS GEMM. We assume column-major storage, so we call BLAS with trans

template <>
my_matrix<float> my_matrix<float>::operator*(const my_matrix<float>& B) const
{
  // A is (*this)
  const my_matrix<float>& A = *this;

  // dimension compatibility check: A.columns must equal B.rows
  if (A.columns != B.rows) {
    throw "incompatible dimensions in operator* my_matrix<float>";
  }

  my_matrix<float> C(A.rows, B.columns);

  // BLAS GEMM parameters
  char transA = 'N';
  char transB = 'N';

  int M = A.rows;        // rows of op(A)
  int N = B.columns;     // cols of op(B)
  int K = A.columns;     // cols of op(A) = rows of op(B)

  float alpha = 1.0f;
  float beta  = 0.0f;

  int lda = A.rows;
  int ldb = B.rows;
  int ldc = C.rows;

  // A.pt[0] points to the contiguous block storing A in column-major order
  sgemm(&transA, &transB,
        &M, &N, &K,
        &alpha,
        A.pt[0], &lda,
        B.pt[0], &ldb,
        &beta,
        C.pt[0], &ldc);

  return C;
}

template <>
my_matrix<double> my_matrix<double>::operator*(const my_matrix<double>& B) const
{
  const my_matrix<double>& A = *this;

  if (A.columns != B.rows) {
    throw "incompatible dimensions in operator* my_matrix<double>";
  }

  my_matrix<double> C(A.rows, B.columns);

  char transA = 'N';
  char transB = 'N';

  int M = A.rows;
  int N = B.columns;
  int K = A.columns;

  double alpha = 1.0;
  double beta  = 0.0;

  int lda = A.rows;
  int ldb = B.rows;
  int ldc = C.rows;

  dgemm(&transA, &transB,
        &M, &N, &K,
        &alpha,
        A.pt[0], &lda,
        B.pt[0], &ldb,
        &beta,
        C.pt[0], &ldc);

  return C;
}



// operator| specializations

// X = A | B means: A * X = B
// We use LAPACK GESV. It overwrites A and B, so we will use copies.

template <>
my_matrix<float> my_matrix<float>::operator|(const my_matrix<float>& B) const
{
  const my_matrix<float>& A = *this;

  // A must be square and compatible with B
  if (A.rows != A.columns) {
    throw "A not square in operator| my_matrix<float>";
  }

  // check that A.rows == B.rows for compatibility
  if (B.rows != A.rows) {
    throw "incompatible dimensions in operator| my_matrix<float>";
  }

  int n    = A.rows;
  int nrhs = B.columns;

  // make copies so we do not modify inputs
  my_matrix<float> Awork(A); // overwritten by sgesv
  my_matrix<float> X(B);     // overwritten to solution by sgesv

  int lda = n;
  int ldb = n;

  int* ipiv = new int[n];
  int info  = 0;

  sgesv(&n, &nrhs,
        Awork.pt[0], &lda,
        ipiv,
        X.pt[0], &ldb,
        &info);

  delete[] ipiv;

  if (info < 0) {
    throw "invalid argument in sgesv called by operator| my_matrix<float>";
  }
  if (info > 0) {
    throw "matrix A not invertible in operator| my_matrix<float>";
  }

  return X;
}

template <>
my_matrix<double> my_matrix<double>::operator|(const my_matrix<double>& B) const
{
  const my_matrix<double>& A = *this;

  if (A.rows != A.columns) {
    throw "A not square in operator| my_matrix<double>";
  }
  if (B.rows != A.rows) {
    throw "incompatible dimensions in operator| my_matrix<double>";
  }

  int n    = A.rows;
  int nrhs = B.columns;

  my_matrix<double> Awork(A);
  my_matrix<double> X(B);

  int lda = n;
  int ldb = n;

  int* ipiv = new int[n];
  int info  = 0;

  dgesv(&n, &nrhs,
        Awork.pt[0], &lda,
        ipiv,
        X.pt[0], &ldb,
        &info);

  delete[] ipiv;

  if (info < 0) {
    throw "invalid argument in dgesv called by operator| my_matrix<double>";
  }
  if (info > 0) {
    throw "matrix A not invertible in operator| my_matrix<double>";
  }

  return X;
}
