#include "../include/matrix.h"



int main(int argc, char* argv[]) 
{
    srand(time(0));

    size_t sz = 10;
    int** a = generate_matrix(sz, sz);
    int** b = generate_matrix(sz, sz);

    print_matrix(sz, sz, a);
    printf("\n  *\n");
    print_matrix(sz, sz, b);
    printf("\n  =\n");

    // measure exectution time
    clock_t start = clock();
    int** result =  matrix_multiplication_squared(sz, sz, a, b);
    clock_t end  = clock();

    float diff = (float) (end - start) / CLOCKS_PER_SEC;
    printf("exec. time: %f\n", diff);

    initialize_threads(sz, a, b);

    free_matrix(sz, sz, a);
    free_matrix(sz, sz, b);
    free_matrix(sz, sz, result);

    

    return 0;
}

/* -------------------------------------------------------------------- */


