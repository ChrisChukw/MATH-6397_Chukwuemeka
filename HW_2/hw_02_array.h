#ifndef HW_02_ARRAY_H
#define HW_02_ARRAY_H

// function prototypes
double mysquare(double x);
double mycube(double x);

// function pointer: takes double, returns double modified by the function pointer
void modif_array(double tab[], int len, double (*f)(double));

#endif