#include "stdio.h"
#include "stdlib.h"
#include "array_functions.h"
#include "mpi.h"

// Prints red
#define RED_COLOR "\x1b[31m"
#define RESET_COLOR "\x1b[0m"

#define SIZE 10000000
#define LIMIT 100

void print_mpi_info(int rank)
{
#ifndef NDEBUG
    if (rank == 0)
    {
        int mpi_version, mpi_subversion;
        MPI_Get_version(&mpi_version, &mpi_subversion);
        printf("MPI version: %d.%d\n", mpi_version, mpi_subversion);
    }
#endif
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    int rank, num_procs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    print_mpi_info(rank);

    int *array = create_array(SIZE, LIMIT);

    double result = 0;
    double start, end;
    int n = 100;
    result = 0;
    int global_index;
    for (int i = 0; i < n; i++)
    {

        MPI_Bcast(array, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

        if (rank == 0)
        {
            start = MPI_Wtime();
        }
        int target_index = parallel_max(array, SIZE, rank, num_procs);
        MPI_Barrier(MPI_COMM_WORLD);
        if (rank == 0)
        {
            end = MPI_Wtime();
            result += end - start;
        }

        MPI_Reduce(&target_index, &global_index, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    }

    if (rank == 0)
    {
        printf("%lf\n", result / n);
    }

    MPI_Finalize();
    free(array);
    return 0;
}
