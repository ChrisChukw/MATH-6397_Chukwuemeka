#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MATRIX_2D_H
#define MATRIX_2D_H

typedef struct {
  // matrix dim
  int rows;
  int columns;

  // pointer of pointer to store matrix entries so we can access pt[i][j]
  double **pt;

  // matrix name tag
  char *tag;

  // status check: 1 if properly defined, 0 otherwise
  int status;

} matrix;


// constructor of matrix
matrix matrix_constructor(int n1, int n2, char *tag);

// destructor of matrix
void matrix_destructor(matrix *m);

// set matrix element
void matrix_set(matrix m, int i, int j, double value);

// get matrix element
double matrix_get(matrix m, int i, int j);

// add two matrices
matrix matrix_add(matrix m1, matrix m2, char *tag);

// product of two matrices
matrix matrix_product(matrix m1, matrix m2, char *tag);

// read a matrix from a file
matrix matrix_read(char *filename, char *tag);

// write a matrix to a file 
void matrix_write(matrix m);

#endif
