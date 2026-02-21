#include "hw2_sine_func.h"
#include <math.h>

// a function that takes an integer n and returns n! as a double
double myfactorial(int n) {

    // validation check: if n is negative, return 0.0
    if (n < 0) return 0.0;

    // initial value of factorial is 1.0, then multiply by 2,3,...,n
    double num_factorial = 1.0;
    for (int k = 2; k <= n; k++) {
        num_factorial *= (double)k;
    }
    return num_factorial;
}

// a function that takes a real x and a tolerance eps, and returns an approximation of sin(x) using the Taylor series expansion
double mysin(double x, double eps) {

    // validation check: eps must be positive, otherwise return 0.0
    if (eps <= 0.0) {
        return 0.0;
    }

    // initialize N to 0
    int N = 0;

    // use fabs to get the absolute value of x
    double abs_x = fabs(x);

    while (pow(abs_x, 2 * N + 3) / myfactorial(2 * N + 3) > eps) {
        N++;
    }

    // return sum_{n=0}^N (-1)^n x^(2n+1) / (2n+1)! (approximation of sin(x))
    // initialize sum to 0.0, then add each term of the series
    double sum = 0.0;

    // use a for loop to compute the sum of the series up to N terms
    for (int n = 0; n <= N; n++) {
        double term = pow(x, 2 * n + 1) / myfactorial(2 * n + 1);
        if (n % 2 == 1) term = -term;
        sum += term;
    }

    return sum;
}