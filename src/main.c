#include "../include/matrix.h"

int** a;
int** b;


void mutliplication_serial_nonsquared(size_t row1, size_t col1, size_t row2, size_t col2)
{
    int status = check_matrix_dimensions(row1, col1, row2, col2);
    if (status == 0) 
    {
        perror("dimension mismatch");
        return;         // dimensions are not matching
    }

    
}

/**
 * performs a normal matrix mutliplication using one core. 
 * is the minimal implementation for a correct computation.
 * is used to benchmark and compare different implementations.
*/
void multiplication_serial(size_t sz)
{
    // measure exectution time
    double start  = get_current_time();
    int**  result = matrix_multiplication_squared(sz, sz, a, b);
    double end    = get_current_time();

    double diff = end - start;
    printf("exec. time: %f\n", diff);

    free_matrix(sz, sz, result);
}


/**
 * performs a matrix multiplication using several threads. for a matrix
 * with size `sz x sz` there are sz threads created. each thread computes
 * the result for one row.
*/
void multiplication_parallel_naive(size_t sz)
{
    int** result = allocate_matrix(sz, sz);

    double start = get_current_time();
    initialize_threads_naive(sz, a, b, result);
    double end   = get_current_time();

    double diff2 = end - start;
    printf("exec. time: %f\n", diff2);

    free_matrix(sz, sz, result);
}


void multiplication_parallel_seminaive(size_t sz) 
{
    int** result = allocate_matrix(sz, sz);

    double start = get_current_time();
    initialize_threads_seminaive(sz, a, b, result);
    double end   = get_current_time();

    double diff2 = end - start;
    printf("exec. time: %f\n", diff2);

    free_matrix(sz, sz, result);
}


int main(int argc, char* argv[]) 
{
    srand(time(0));
    

    size_t sz = 1000;
    a = generate_matrix(sz, sz);
    b = generate_matrix(sz, sz);

    printf("multiplication serial: \n");
    multiplication_serial(sz);
    printf("\n");

    printf("multiplication parallel: \n");
    // clock measures CPU time, as several threads are sed for computation
    clock_t start = clock();
    multiplication_parallel_naive(sz);
    clock_t end   = clock();

    double diff = (double) (end - start) / CLOCKS_PER_SEC;
    printf("cpu uptime: %f\n", diff);

    printf("\n");
    printf("multiplication parallel-seminaive: \n");
    multiplication_parallel_seminaive(sz);

    free_matrix(sz, sz, a);
    free_matrix(sz, sz, b);

    a = generate_matrix(20, 10);
    b = generate_matrix(10, 40);
    int** result = allocate_matrix(20, 40);

    result = matrix_multiplication(20, 10, 10, 40, a, b);
    //print_matrix(20, 40, result);

    free_matrix(20, 10, a);
    free_matrix(10, 40, b);
    free_matrix(20, 40, result);

    return 0;
}

/* -------------------------------------------------------------------- */


