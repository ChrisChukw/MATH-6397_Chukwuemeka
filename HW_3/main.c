#include "matrix_2D.h"

int main(void){

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

  // Call destructors
  matrix_destructor(&ma);
  matrix_destructor(&mb);
  matrix_destructor(&maplusmb);
  matrix_destructor(&maxb);

  return 0;
}
