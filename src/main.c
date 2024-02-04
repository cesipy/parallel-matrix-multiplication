#include "../include/matrix.h"


/**
 * performs a normal matrix mutliplication using one core. 
 * is the minimal implementation for a correct computation.
 * is used to benchmark and compare different implementations.
*/
void multiplication_serial(size_t sz)
{
    int** a = generate_matrix(sz, sz);
    int** b = generate_matrix(sz, sz);

    // measure exectution time
    double start  = get_current_time();
    int**  result = matrix_multiplication_squared(sz, sz, a, b);
    double end    = get_current_time();

    double diff = end - start;
    printf("exec. time: %f\n", diff);

    free_matrix(sz, sz, a);
    free_matrix(sz, sz, b);
    free_matrix(sz, sz, result);
}



/**
 * performs a matrix multiplication using several threads. for a matrix
 * with size `sz x sz` there are sz threads created. each thread computes
 * the result for one row.
*/
void multiplication_parallel(size_t sz)
{
    int** a = generate_matrix(sz, sz);
    int** b = generate_matrix(sz, sz);
    int** result = allocate_matrix(sz, sz);

    double start = get_current_time();
    initialize_threads_naive(sz, a, b);
    double end = get_current_time();

    double diff2 = end - start;
    printf("exec. time: %f\n", diff2);

    free_matrix(sz, sz, a);
    free_matrix(sz, sz, b);
    free_matrix(sz, sz, result);
}


int main(int argc, char* argv[]) 
{
    srand(time(0));

    size_t sz = 800;

    printf("multiplication serial: \n");
    multiplication_serial(sz);
    printf("\n");


    printf("multiplication parallel: \n");
    // clock measures CPU time, as several threads are sed for computation
    clock_t start = clock();
    multiplication_parallel(sz);
    clock_t end   = clock();

    double diff = (double) (end - start) / CLOCKS_PER_SEC;
    printf("cpu uptime: %f\n", diff);

    return 0;
}

/* -------------------------------------------------------------------- */


