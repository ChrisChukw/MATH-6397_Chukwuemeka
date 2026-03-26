#include "matrix_2D.h"
#include "gauss_elimination.h"

int main(void){

                      // Part I
  //  read matrices from files matrix_A and matrix_B
  //  set their tags to "ma" and "mb"
  matrix ma = matrix_read("matrices/matrix_A", "ma");
  matrix mb = matrix_read("matrices/matrix_B", "mb");

  //  Sum: store in maplusmb, set tag "maplusmb", write result with matrix_write
  matrix maplusmb = matrix_add(ma, mb, "maplusmb");
  matrix_write(maplusmb);

  // Product: store in maxb, set tag to "maxmb", write result with matrix_write
  matrix maxb = matrix_product(ma, mb, "maxmb");
  matrix_write(maxb);


                         // Part II
  // inverse of ma -> ma_inverse (tag "ma_inverse"), write result with matrix_write
  matrix ma_inverse = matrix_gauss_inverse(ma, "ma_inverse");
  matrix_write(ma_inverse);

  // Call destructors
  matrix_destructor(&ma);
  matrix_destructor(&mb);
  matrix_destructor(&maplusmb);
  matrix_destructor(&maxb);
  matrix_destructor(&ma_inverse);

  return 0;
}

//note: I put matrix_A and matrix_B in a subfolder called matrices

// compile with:
// gcc -std=c11 main.c matrix_2D.c gauss_elimination.c -lm -o matrix_exe

// run with:
// ./matrix_exe
