#include <iostream>
#include "my_matrix.hh"

int main(void) {

  // try block to catch exceptions thrown by my_matrix methods
  try {


    // F1: a (2,3) matrix of floats with all entries equal to 1.0
    my_matrix<float> F1(2, 3);
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 3; j++) {
        F1(i, j) = 1.0f;
      }
    }

    // F3 = F1 + F1. We display  result line by line
    my_matrix<float> F3 = F1 + F1;
    std::cout << "F3 = F1 + F1:" << std::endl;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 3; j++) {
        std::cout << F3(i, j) << " ";
      }
      std::cout << std::endl;
    }

    // F2: a (3,3) matrix of all 2's
    my_matrix<float> F2(3, 3);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        F2(i, j) = 2.0f;
      }
    }

    // F4 = F1 * F2. We display result line by line
    my_matrix<float> F4 = F1 * F2;
    std::cout << "F4 = F1 * F2:" << std::endl;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 3; j++) {
        std::cout << F4(i, j) << " ";
      }
      std::cout << std::endl;
    }

  }

  // catch exceptions and print error message
  catch (const char* e) {
    std::cout << e << std::endl;
    return 1;
  }

  return 0;
}
