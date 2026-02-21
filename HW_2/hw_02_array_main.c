#include <stdio.h>
#include "hw_02_array.h"

int main(void) {

    // initialize an array of doubles
    double tab[] = {2.0, 2.5, 3.9};
    int len = 3;

    // square all the elements of tab using the function pointer to mysquare
    modif_array(tab, len, mysquare);

    // Print tab[0] and tab[1]
    printf("tab[0] = %.6f\n", tab[0]);
    printf("tab[1] = %.6f\n", tab[1]);

    // take the cube of all the elements of tab using the function pointer to mycube
    // Note: this will modify the already squared values in tab
    modif_array(tab, len, mycube);

    // Print tab[0] and tab[1] again
    printf("tab[0] = %.6f\n", tab[0]);
    printf("tab[1] = %.6f\n", tab[1]);

    return 0;
}