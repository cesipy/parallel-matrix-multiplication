#include "../include/matrix.h"

int** generate_matrix(size_t rows, size_t cols) 
{
    
    int** a = allocate_matrix(rows, cols);

    for (int i=0; i<rows; i++) 
    {
        for (int j=0; j<cols; j++)
        {
            int random_number = rand() %  (MAX_RANDOM +1 - MIN_RANDOM) + MIN_RANDOM;
            a[i][j] = random_number;
        }
    }

    return a;
}


void free_matrix(size_t rows, size_t cols, int** a) 
{
    for (int i=0; i<rows; i++)
    {
        free(a[i]);
    }

    free(a);
}


int** allocate_matrix(size_t rows, size_t cols) 
{
    int** a = (int**)malloc(rows * sizeof(int*));
    for (int i=0; i<rows; i++) 
    {
        a[i] = (int*)malloc(cols * sizeof(int));
    }

    return a;
}