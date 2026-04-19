#include <iostream>
#include "my_matrix.hh"

int main(void) {

  try {

    // F1: (2,3) float, all ones
    my_matrix<float> F1(2, 3);
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 3; j++) {
        F1(i, j) = 1.0f;
      }
    }

    // F3 = F1 + F1, display line by line
    my_matrix<float> F3 = F1 + F1;
    std::cout << "F3 = F1 + F1:" << std::endl;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 3; j++) {
        std::cout << F3(i, j) << " ";
      }
      std::cout << std::endl;
    }

    // F2: (3,3) float, all twos
    my_matrix<float> F2(3, 3);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        F2(i, j) = 2.0f;
      }
    }

    // F4 = F1 * F2, display line by line
    my_matrix<float> F4 = F1 * F2;
    std::cout << "F4 = F1 * F2:" << std::endl;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 3; j++) {
        std::cout << F4(i, j) << " ";
      }
      std::cout << std::endl;
    }

  }
  catch (const char* e) {
    std::cout << e << std::endl;
    return 1;
  }

  return 0;
}
