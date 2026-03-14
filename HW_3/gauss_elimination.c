#include <math.h>
#include "gauss_elimination.h"


// function to swap two rows of a matrix (row n1 <-> row n2)
void matrix_swap_row(matrix m, int n1, int n2)
{
  // Check status and bounds
  if (m.status == 0) {
    printf("function matrix_swap_row; matrix has status 0\n");
    return;
  }
  if (n1 < 0 || n1 >= m.rows || n2 < 0 || n2 >= m.rows) {
    printf("function matrix_swap_row; row index out of bounds for matrix \n");
    return;
  }

  // swap pointers to rows n1 and n2. Not sure if a, b = b, a works in C, so did it manually with a temp variable.
  double *tmp = m.pt[n1];
  m.pt[n1] = m.pt[n2];
  m.pt[n2] = tmp;
}


// function to divide row n1 by a real r (r must be non-zero)
void matrix_divide_row(matrix m, int n1, double r)
{
  // Check status and bounds
  if (m.status == 0) {
    printf("function matrix_divide_row; matrix has status 0\n");
    return;
  }
  if (n1 < 0 || n1 >= m.rows) {
    printf("function matrix_divide_row; row index out of bounds for matrix \n");
    return;
  }

  // check division by zero
  if (r == 0.0) {
    printf("function matrix_divide_row; division by zero for matrix \n");
    return;
  }

  // divide each entry in row n1 by r
  for (int j = 0; j < m.columns; j++) {
    matrix_set(m, n1, j, matrix_get(m, n1, j) / r);
  }
}


// function to subtract r * row n2 from row n1
void matrix_subtract_row(matrix m, int n1, int n2, double r)
{
    // Check status and bounds
  if (m.status == 0) {
    printf("function matrix_subtract_row; matrix has status 0\n");
    return;
  }
  if (n1 < 0 || n1 >= m.rows || n2 < 0 || n2 >= m.rows) {
    printf("function matrix_subtract_row; row index out of bounds for matrix \n");
    return;
  }

  // row n1 <- row n1 - r * row n2
  for (int j = 0; j < m.columns; j++) {
    double v = matrix_get(m, n1, j) - r * matrix_get(m, n2, j);
    matrix_set(m, n1, j, v);
  }
}


// Compute inverse using GEM
matrix matrix_gauss_inverse(matrix m, char *tag)
{
  matrix inv;

  // default; NULL matrix 
  inv.rows = 0;
  inv.columns = 0;
  inv.pt = NULL;
  inv.status = 0;
  inv.tag = (tag != NULL) ? strdup(tag) : NULL;

  // return NULL matrix if input matrix is not allocated correctly
  if (m.status == 0) {
    printf("function matrix_gauss_inverse; input matrix has status 0\n");
    return inv;
  }

  // return NULL matrix if input matrix is not square
  if (m.rows != m.columns) {
    printf("function matrix_gauss_inverse; input matrix is not square\n");
    return inv;
  }

  int n = m.rows;

  // make copies so we do NOT modify input matrix m
  matrix A = matrix_constructor(n, n, "A_copy");
  matrix I = matrix_constructor(n, n, "I_copy");

  // check status of matrices
  if (A.status == 0 || I.status == 0) {
    printf("function matrix_gauss_inverse; could not make copies of input matrix\n");
    matrix_destructor(&A);
    matrix_destructor(&I);
    return inv; 
  }

  // populate A with m, and I with identity
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix_set(A, i, j, matrix_get(m, i, j));
      matrix_set(I, i, j, (i == j) ? 1.0 : 0.0);
    }
  }

  // Gauss-Jordan elimination with partial pivoting
  for (int k = 0; k < n; k++) {

    // Pivot search
    int pivot = k;
    double maxabs = fabs(matrix_get(A, k, k));
    for (int i = k + 1; i < n; i++) {
      double val = fabs(matrix_get(A, i, k));
      if (val > maxabs) {
        maxabs = val;
        pivot = i;
      }
    }

    // if max pivot is 0, column k cannot be used to create a pivot -> NOT invertible
    if (maxabs == 0.0) {
      printf("function matrix_gauss_inverse; matrix is not invertible (zero pivot)\n");

      // return a ZERO matrix
      matrix_destructor(&A);
      matrix_destructor(&I);

      matrix z = matrix_constructor(n, n, tag);
      if (z.status == 0) {
        return inv; 
      }
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          matrix_set(z, i, j, 0.0);
        }
      }

      // free memory
      matrix_destructor(&inv);
      return z;
    }

    // swap pivot row into position k
    if (pivot != k) {
      matrix_swap_row(A, pivot, k);
      matrix_swap_row(I, pivot, k);
    }

    // normalize pivot row
    double piv = matrix_get(A, k, k);
    matrix_divide_row(A, k, piv);
    matrix_divide_row(I, k, piv);

    // eliminate other rows
    for (int i = 0; i < n; i++) {
      if (i == k) continue;

      double r = matrix_get(A, i, k);
      if (r != 0.0) {
        matrix_subtract_row(A, i, k, r);
        matrix_subtract_row(I, i, k, r);
      }
    }
  }

  // at this point, A should be the identity, and I should be the inverse of m. 
  // We will return I, but first we need to copy it into a new matrix with the correct tag 

  matrix_destructor(&inv); // free default NULL matrix

  inv = matrix_constructor(n, n, tag);
  if (inv.status == 0) {
    matrix_destructor(&A);
    matrix_destructor(&I);

    // return NULL matrix with correct tag
    inv.rows = 0;
    inv.columns = 0;
    inv.pt = NULL;
    inv.status = 0;
    inv.tag = (tag != NULL) ? strdup(tag) : NULL;
    return inv;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix_set(inv, i, j, matrix_get(I, i, j));
    }
  }

  matrix_destructor(&A);
  matrix_destructor(&I);

  return inv;
}
