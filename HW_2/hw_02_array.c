#include "hw_02_array.h"

// function that takes a double and returns its square
double mysquare(double x) {
    return x * x;
}

// function that modifies an array of doubles using a function pointer
void modif_array(double tab[], int len, double (*f)(double)) {
    for (int i = 0; i < len; i++) {
        tab[i] = f(tab[i]);
    }
}

// function that takes a double and returns its cube
double mycube(double x) {
    return x * x * x;
}