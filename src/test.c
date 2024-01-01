#include "../include/matrix.h"

#include <assert.h>


int test_result(size_t rows, size_t cols, int** matrix_to_test, int valid_result[rows][cols])
{
    for (int i=0; i<rows; i++) 
    {
        for (int j=0; j<cols; j++)
        {
            if (matrix_to_test[i][j] != valid_result[i][j])
            {
                printf("Test failed at [%d][%d]: Expected %d, Got %d\n", i, j, valid_result[i][j], matrix_to_test[i][j]);
                return 0;
            }
        }
    }

    printf("test passed!\n");
    return 1;
}


void tests()
{
    size_t sz = 3;
    int** a = allocate_matrix(sz, sz);
    int** b = allocate_matrix(sz, sz);

    initialize_matrix(sz, sz, a, test_matrix1);
    initialize_matrix(sz, sz, b, test_matrix2);

    int** res = matrix_multiplication_squared(sz, sz, a, b);
    
    test_result(sz, sz, res, result_matrix_1x2);
    // TODO: handle tests

    free_matrix(sz, sz, a);
    free_matrix(sz, sz, b);
    free_matrix(sz, sz, res);

}

int main() 
{
    tests();
}




/* ---------------------------------- */
int test_matrix1[3][3] = {
    {10, 1, 123}, 
    {-5, 3, 11}, 
    {7, -15, 9}
};

int test_matrix2[3][3] = {
    {-14, 3, -2}, 
    {6, 7, 8}, 
    {-4, 1, 15}
};

int result_matrix_1x2[3][3] = {
    {-626, 160, 1833}, 
    {44, 17, 199}, 
    {-224, -75, 1}
};

int test_matrix3[4][4] = {
    {0, 1, 2, 3}, 
    {4, 5, 6, 7}, 
    {8, 9, 10, 11}, 
    {12, 13, 14, 15}
};

