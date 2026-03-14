#include "matrix_2D.h"

// Avoid warning for std=c99 or std=c11 
char *strdup(const char *str_in)
{
  int n = (int)strlen(str_in) + 1;              // Input length + end string
  char *str_out = (char *)malloc(n * sizeof(char)); // Allocation
  if (str_out != NULL) {                        // Check if malloc was successful
    strcpy(str_out, str_in);
  }
  return str_out;
}

// matrix constructor
matrix matrix_constructor(int n1, int n2, char *tag)
{

// function to construct a matrix with n1 rows and n2 columns, and tag as the name of the matrix

  matrix m;

  // initialize to NULL matrix
  m.rows = 0;
  m.columns = 0;
  m.pt = NULL;
  m.tag = NULL;
  m.status = 0;

  // check dimensions
  if (n1 < 1 || n2 < 1) {
    printf("function matrix_constructor; dimensions must be >= 1\n");
    return m;
  }

  // allocate tag using strdup
  if (tag != NULL) {
    m.tag = strdup(tag);
    if (m.tag == NULL) {
      printf("function matrix_constructor; could not allocate tag\n");
      return m;
    }
  } else {
    // if tag is NULL, leave as NULL and print a warning
    printf("function matrix_constructor; warning - tag is NULL\n");
    m.tag = NULL;
  }

  // pointer of pointer so entries are accessible with pt[i][j]
  m.pt = (double **)malloc(n1 * sizeof(double *));
  if (m.pt == NULL) {
    printf("function matrix_constructor; could not allocate pointers\n");
    free(m.tag);
    m.tag = NULL;
    return m;
  }

  // allocate the rows
  for (int i = 0; i < n1; i++) {
    m.pt[i] = (double *)malloc(n2 * sizeof(double));
    if (m.pt[i] == NULL) {
      printf("function matrix_constructor; could not allocate row %d\n", i);

      // free previously allocated rows
      for (int k = 0; k < i; k++) {
        free(m.pt[k]);
      }
      free(m.pt);
      m.pt = NULL;
      free(m.tag);
      m.tag = NULL;
      return m;
    }
  }

  // at this point, allocation succeeded! yes!
  m.rows = n1;
  m.columns = n2;
  m.status = 1;

  return m;
}


// matrix destructor
void matrix_destructor(matrix *m)
{
  if (m != NULL) {
    if (m->status != 0) {
      // free elements first
      if (m->pt != NULL) {
        for (int i = 0; i < m->rows; i++) {
          free(m->pt[i]);
        }
        free(m->pt);
      }

      // then free tag
      if (m->tag != NULL) {
        free(m->tag);
      }

      // reset fields to NULL/0
      m->pt = NULL;
      m->tag = NULL;
      m->rows = 0;
      m->columns = 0;
      m->status = 0;
    } else {
      
      m->pt = NULL;
      if (m->tag != NULL) {
        free(m->tag);
        m->tag = NULL;
      }
      m->rows = 0;
      m->columns = 0;
      m->status = 0;
    }
  }
}


// function to set matrix element
void matrix_set(matrix m, int i, int j, double value)
{
 // if status is 0, print warning and return without setting
  if (m.status == 0) {
    printf("function matrix_set; matrix has status 0\n");
    return;
  }

  // check index bounds
  if (i < 0 || i >= m.rows || j < 0 || j >= m.columns) {
    printf("function matrix_set; index out of bounds for matrix\n");
    return;
  }

  //if everything checks out, set the value
  m.pt[i][j] = value;
}


// function to get  matrix element
double matrix_get(matrix m, int i, int j)
{
  // if status is 0, print warning and return 0.0
  if (m.status == 0) {
    printf("function matrix_get; matrix has status 0\n");
    return 0.0;
  }

  // check index bounds
  if (i < 0 || i >= m.rows || j < 0 || j >= m.columns) {
    printf("function matrix_get; index out of bounds for matrix\n");
    return 0.0;
  }

  // if everything checks out, return the value
  return m.pt[i][j];
}


// add two matrices
matrix matrix_add(matrix m1, matrix m2, char *tag)
{
  matrix out;

  // default NULL matrix
  out.rows = 0;
  out.columns = 0;
  out.pt = NULL;
  out.tag = NULL;
  out.status = 0;

  // check status of input matrices
  if (m1.status == 0) {
    printf("function matrix_add; matrix has status 0\n");
    return out;
  }
  if (m2.status == 0) {
    printf("function matrix_add; matrix has status 0\n");
    return out;
  }

  // check that dimensions match
  if (m1.rows != m2.rows || m1.columns != m2.columns) {
    printf("function matrix_add; incompatible dimensions for matrices\n");
    return out;
  }

  out = matrix_constructor(m1.rows, m1.columns, tag);
  if (out.status == 0) {
    return out;
  }

  // add the entries
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m1.columns; j++) {
      matrix_set(out, i, j, matrix_get(m1, i, j) + matrix_get(m2, i, j));
    }
  }

  return out;
}

// product of two matrices
matrix matrix_product(matrix m1, matrix m2, char *tag)
{
  matrix out;

  // default NULL matrix
  out.rows = 0;
  out.columns = 0;
  out.pt = NULL;
  out.tag = NULL;
  out.status = 0;

  // check status of input matrices
  if (m1.status == 0) {
    printf("function matrix_product; matrix has status 0\n");
    return out;
  }
  if (m2.status == 0) {
    printf("function matrix_product; matrix has status 0\n");
    return out;
  }

  // dimension check: (m1.rows x m1.columns) * (m2.rows x m2.columns) requires m1.columns == m2.rows
  if (m1.columns != m2.rows) {
    printf("function matrix_product; incompatible dimensions for matrices\n");
    return out;
  }

  out = matrix_constructor(m1.rows, m2.columns, tag);
  if (out.status == 0) {
    return out;
  }

  // compute the product using the standard triple loop
  for (int i = 0; i < out.rows; i++) {
    for (int j = 0; j < out.columns; j++) {
      double s = 0.0;
      for (int k = 0; k < m1.columns; k++) {
        s += matrix_get(m1, i, k) * matrix_get(m2, k, j);
      }
      matrix_set(out, i, j, s);
    }
  }

  return out;
}


// read a matrix from a file
matrix matrix_read(char *filename, char *tag)
{
  matrix out;

  // default NULL matrix
  out.rows = 0;
  out.columns = 0;
  out.pt = NULL;
  out.tag = NULL;
  out.status = 0;

  // open the file for reading
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("function matrix_read; could not open file %s\n", filename);
    return out;
  }

  // read dimensions from the file
  int r, c;
  if (fscanf(fp, "%d %d", &r, &c) != 2) {
    printf("function matrix_read; could not read dimensions from file %s\n", filename);
    fclose(fp);
    return out;
  }

  // construct the output matrix
  out = matrix_constructor(r, c, tag);
  if (out.status == 0) {
    fclose(fp);
    return out;
  }

  // read the entries from the file
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      double val;
      if (fscanf(fp, "%lf", &val) != 1) {
        printf("function matrix_read; not enough entries in file %s\n", filename);
        matrix_destructor(&out);
        fclose(fp);
        // return NULL matrix
        out.rows = 0;
        out.columns = 0;
        out.pt = NULL;
        out.tag = NULL;
        out.status = 0;
        return out;
      }
      matrix_set(out, i, j, val);
    }
  }

  // close the file and return the output matrix
  fclose(fp);
  return out;
}


// write a matrix to a file (filename = matrix tag)
void matrix_write(matrix m)
{
    // if status is 0, print warning and return without writing
  if (m.status == 0) {
    printf("function matrix_write; matrix has status 0\n");
    return;
  }
  // if tag is NULL, print warning and return without writing
  if (m.tag == NULL) {
    printf("function matrix_write; matrix has status 0\n");
    return;
  }

  // open the file for writing
  FILE *fp = fopen(m.tag, "w");
  if (fp == NULL) {
    printf("function matrix_write; could not open file %s\n", m.tag);
    return;
  }

  // write dimensions to the file
  fprintf(fp, "%d %d\n", m.rows, m.columns);
  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.columns; j++) {
      fprintf(fp, "%.15g", matrix_get(m, i, j));
      if (j < m.columns - 1) fprintf(fp, " ");
    }
    fprintf(fp, "\n");
  }

  // close the file
  fclose(fp);
}
