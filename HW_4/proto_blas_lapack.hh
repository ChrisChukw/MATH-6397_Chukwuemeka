#ifndef PROTO_BLAS_LAPACK_HH
#define PROTO_BLAS_LAPACK_HH

// BLAS/LAPACK Fortran interfaces
#ifndef BLAS_NO_UNDERSCORE
#define sgemm sgemm_
#define dgemm dgemm_
#define sgesv sgesv_
#define dgesv dgesv_
#endif

extern "C" {

  // BLAS: for float
  void sgemm_(const char* TRANSA, const char* TRANSB,
              const int* M, const int* N, const int* K,
              const float* ALPHA,
              const float* A, const int* LDA,
              const float* B, const int* LDB,
              const float* BETA,
              float* C, const int* LDC);

// BLAS: for double
  void dgemm_(const char* TRANSA, const char* TRANSB,
              const int* M, const int* N, const int* K,
              const double* ALPHA,
              const double* A, const int* LDA,
              const double* B, const int* LDB,
              const double* BETA,
              double* C, const int* LDC);


  // LAPACK: for float
  void sgesv_(const int* N, const int* NRHS,
              float* A, const int* LDA,
              int* IPIV,
              float* B, const int* LDB,
              int* INFO);

  // LAPACK: for double
  void dgesv_(const int* N, const int* NRHS,
              double* A, const int* LDA,
              int* IPIV,
              double* B, const int* LDB,
              int* INFO);
}

#endif
