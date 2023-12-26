#include "stdio.h"
#include "stdlib.h"
#include "array_functions.h"

#include "mpi.h"

#define RED_COLOR "\x1b[31m"
#define RESET_COLOR "\x1b[0m"

#define SIZE 10000000
#define LIMIT 100
//#define SEED 920215

void print_mpi_info()
{
#ifndef NDEBUG
    int mpi_version, mpi_subversion;
    MPI_Get_version(&mpi_version, &mpi_subversion);
    printf("MPI version: %d.%d\n", mpi_version, mpi_subversion);
#endif
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Получение номера текущего процесса
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Получение общего количества процессов

    
    int *array = create_array(SIZE, LIMIT);
    //print_array(array, SIZE);

    double result = 0;
    double start, end;
    int n = 100;

    
    //for(int num_proc = 1; num_proc <= size; num_proc++)
    //{
        result = 0;
        
        for(int i = 0; i < n; i++)
        {  

            MPI_Bcast(array, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

            if(rank == 0) {start = MPI_Wtime();}
            int target_index = parallel_max(array, SIZE, rank, size);
            MPI_Barrier(MPI_COMM_WORLD);
            if(rank == 0) { end = MPI_Wtime();
            result += end - start;}

            int global_index;
            MPI_Reduce(&target_index, &global_index, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

        }
        if(rank == 0) {printf("%lf\n", result/n);}
    //}


    /*if (rank == 0) {
        if (global_index != -1) {
            printf("Element found at index: %d\n", global_index);
        } else {
            printf("Element not found in the array.\n");
        }
    }*/
    

    free(array);

    MPI_Finalize();
    return 0;
}