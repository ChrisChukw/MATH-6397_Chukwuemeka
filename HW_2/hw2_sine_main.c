#include <stdio.h>
#include <stdlib.h>   
#include <math.h>   
#include "hw2_sine_func.h"

int main(int argc, char *argv[]) {

    // validation check
    if (argc != 3) {
        printf("Need three arguments: executable, real x (double) and tolerance eps (double).\n");
        return 0;
    }

    // show the arguments
    printf("argv[0] = %s\n", argv[0]);
    printf("argv[1] = %s\n", argv[1]);
    printf("argv[2] = %s\n", argv[2]);

    // Convert argv[1] to x and argv[2] to eps
    double x   = atof(argv[1]);
    double eps = atof(argv[2]);

    // extra validation using sscanf 
    int arg1_ok = sscanf(argv[1], "%lf", &x);
    int arg2_ok = sscanf(argv[2], "%lf", &eps);
    printf("arg1_ok=%d arg2_ok=%d\n", arg1_ok, arg2_ok);

     // Print sin(x), the value of sin(x) computed by the math library function sin
    printf("sin(%.4f) = %.10f\n", x, sin(x));

    // Print mysin(x), my approximation of sin(x)
    printf("mysin(%.4f)=%.10f\n", x, mysin(x, eps));


    return 0;
}