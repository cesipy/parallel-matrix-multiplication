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

   // print_matrix(rows, cols, result_matrix);
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
    int** res = param->result_matrix;
    int** a   = param->a;
    int** b   = param->b;
    int a_i   = param->a_i;
    int a_j   = 0;
    int sz    = param->sz;
    int sum   = 0;

    for (int i=0; i<sz; i++)
    {
        sum = 0;
        for (int j=0; j<sz; j++)
        {
            sum += a[a_i][j] * b[j][i];
        }
        res[a_i][a_j] = sum;
        a_j += 1;
    }
    
    return NULL;
}


// creates a thread for each entry. therefore, size*size threads are created. 
// because of the overhead for each thread, the current
// implemetation is very unperformant.
int initialize_threads(int size, int** a, int** b) 
{
    int       num_threads = size;
    pthread_t threads[num_threads];
    param_t*  arguments[num_threads];

    int**     result_matrix = allocate_matrix(size, size);

    for (int i=0; i<size; i++)
    {
        arguments[i] = malloc(sizeof(param_t));
        arguments[i]->a = a;
        arguments[i]->b = b;
        arguments[i]->result_matrix = result_matrix;
        arguments[i]->a_i = i;
        arguments[i]->sz = size;

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
    
    printf("\n -\n\nparallel computation: \n");
    //print_matrix(size, size, result_matrix);

    // free argument-array
    for (int i=0; i<num_threads; i++)
    {
        free(arguments[i]);
    }

    return 1;
    
}

double get_current_time()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + now.tv_nsec*1e-9;
}