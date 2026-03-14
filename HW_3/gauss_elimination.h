#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_2D.h"

#ifndef GAUSS_ELIMINATION_H
#define GAUSS_ELIMINATION_H



// swap two rows of a matrix (row n1 <-> row n2)
void matrix_swap_row(matrix m, int n1, int n2);

// divide row n1 by a real r (r must be non-zero)
void matrix_divide_row(matrix m, int n1, double r);

// row n1 <- row n1 - r * row n2
void matrix_subtract_row(matrix m, int n1, int n2, double r);

// compute inverse of a matrix using Gauss elimination
matrix matrix_gauss_inverse(matrix m, char *tag);

#endif
