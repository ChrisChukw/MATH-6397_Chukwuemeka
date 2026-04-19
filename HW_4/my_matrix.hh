#ifndef MY_MATRIX_HH
#define MY_MATRIX_HH

// a template class for 2D matrices stored in column-major order.

template <typename T>
class my_matrix {


// part I.a
private:
  int rows;
  int columns;
  T** pt; // pt[j][i] = element (i,j)


// part I.b
public:
  // default constructor for my matrix
  my_matrix() {
    rows = 1;
    columns = 1;

    // allocation
    pt = new T*[columns];
    pt[0] = new T[rows * columns](); // initialize to 0
    // column pointers
    for (int j = 1; j < columns; j++) {
      pt[j] = pt[0] + j * rows;
    }
  }

  // user constructor for my matrix
  my_matrix(int r, int c) {
    if (r <= 0 || c <= 0) {
      throw "bad dimensions in user_constructor my_matrix(int,int)";
    }

    rows = r;
    columns = c;

    // allocation if dimensions are valid
    pt = new T*[columns];
    pt[0] = new T[rows * columns](); // initialize to 0
    for (int j = 1; j < columns; j++) {
      pt[j] = pt[0] + j * rows;
    }
  }

  // copy constructor
  my_matrix(const my_matrix& m) {
    rows = m.rows;
    columns = m.columns;

    pt = new T*[columns];
    pt[0] = new T[rows * columns];
    for (int j = 1; j < columns; j++) {
      pt[j] = pt[0] + j * rows;
    }

    // copy all entries
    for (int j = 0; j < columns; j++) {
      for (int i = 0; i < rows; i++) {
        pt[j][i] = m.pt[j][i];
      }
    }
  }

  // destructor
  ~my_matrix() {
    if (pt != nullptr) {
      delete[] pt[0];
      delete[] pt;
      pt = nullptr;
    }
  }

  // Operator=: check for self-assignment, check dimensions, copy entries
  my_matrix& operator=(const my_matrix& m) {
    // self-assignment protection
    if (this == &m) return *this;

    if (rows != m.rows || columns != m.columns) {
      throw "dimension mismatch in operator= my_matrix";
    }

    for (int j = 0; j < columns; j++) {
      for (int i = 0; i < rows; i++) {
        pt[j][i] = m.pt[j][i];
      }
    }
    return *this;
  }

  // Operator(): check for index out of bounds, return reference to element (i,j)
  T& operator()(int i, int j) {
    if (i < 0 || j < 0 || i >= rows || j >= columns) {
      throw "index out of bounds in operator() my_matrix";
    }
    return pt[j][i];
  }

//   // extra safety check for const objects
//   const T& operator()(int i, int j) const {
//     if (i < 0 || j < 0 || i >= rows || j >= columns) {
//       throw "index out of bounds in const operator() my_matrix";
//     }
//     return pt[j][i];
//   }


  // Operator+: check for dimension mismatch, return new my_matrix with sum of entries
  my_matrix operator+(const my_matrix& m) const {
    if (rows != m.rows || columns != m.columns) {
      throw "dimension mismatch in operator+ my_matrix";
    }

    my_matrix sum(rows, columns);
    for (int j = 0; j < columns; j++) {
      for (int i = 0; i < rows; i++) {
        sum.pt[j][i] = pt[j][i] + m.pt[j][i];
      }
    }
    return sum;
  }



  // Part I.c:
  my_matrix operator*(const my_matrix& m) const;
  my_matrix operator|(const my_matrix& m) const;
};

// Explicit specialization declarations (definitions will be in my_matrix.cc)
template <>
my_matrix<float> my_matrix<float>::operator*(const my_matrix<float>& m) const;

template <>
my_matrix<double> my_matrix<double>::operator*(const my_matrix<double>& m) const;

template <>
my_matrix<float> my_matrix<float>::operator|(const my_matrix<float>& m) const;

template <>
my_matrix<double> my_matrix<double>::operator|(const my_matrix<double>& m) const;

#endif
