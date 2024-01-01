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

void print_matrix(size_t rows, size_t cols, int** matrix)
{

    for (int i=0; i<rows; i++) 
    {
        for (int j=0; j<cols; j++) 
        {
            printf("%*d ", PADDING,  matrix[i][j]);
        }
        printf("\n");    
    }
}


int** matrix_multiplication_squared(size_t rows, size_t cols, int** a, int** b)
{
    int** result_matrix = allocate_matrix(rows, cols);

    for (int i=0; i<rows; i++) 
    {
        for (int j=0; j<cols; j++) 
        {
            int sum = 0;
            for (int k=0; k<rows; k++)
            {
                sum += a[i][k] * b[k][j];
            }
            result_matrix[i][j] = sum;
        }
    }

    print_matrix(rows, cols, result_matrix);
    return result_matrix;
}


void initialize_matrix(size_t rows, size_t cols, int** alloc_matrix, int matrix[rows][cols]) 
{
    for (int i=0; i<rows; i++) 
    {
        for (int j=0; j<cols; j++)
        {
            alloc_matrix[i][j] = matrix[i][j];
        }
    }
} 

void* thread_function(void* arg) 
{
    param_t* param = arg;

    //TODO: multiplication logic
    return NULL;
}


int initialize_threads(int size, int** a, int** b) 
{
    int       num_threads = size * size;
    pthread_t threads[num_threads];
    param_t*  arguments[num_threads];
    int       index = 0;

    int**     result_matrix = allocate_matrix(size, size);

    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size; j++)
        {
            arguments[index] = malloc(sizeof(param_t));
            arguments[index]->a = a;
            arguments[index]->b = b;
            arguments[index]->result_matrix = result_matrix;
            arguments[index]->a_i = i;
            arguments[index]->a_j = j;

            index += 1;
        }
    }


    /* initialize threads */
    for (int i=0; i<num_threads; i++)
    {
       
        int status = pthread_create(&threads[i], NULL, &thread_function, (void*)arguments[i]);
        if (status != 0)
        {
            perror("thread initialisation");
            free_matrix(num_threads, num_threads, a);
            free_matrix(num_threads, num_threads, b),
            exit(EXIT_FAILURE);
        }
    }

    // join all threads
    for (int i=0; i<num_threads; i++)
    {
        int status = pthread_join(threads[i], NULL);
    }

    
    // free argument-array
    for (int i=0; i<num_threads; i++)
    {
        free(arguments[i]);
    }

    return 1;
    
}