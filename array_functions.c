#include "array_functions.h"

int *create_array(const int num, const int limit)
{
    int *array = NULL; ///< The array we need to find the max in

    /* Generate the random array */
    array = (int *)malloc(num * sizeof(int));
    for (int i = 0; i < num; i++)
    {
        array[i] = rand() % limit;
    }
    return array;
}

void print_array(int *array, int size)
{
    printf("\n");
    if (array == NULL || size < 0)
    {
        printf(RED_COLOR "ERROR in print_array()\n" RESET_COLOR);
        return;
    }
    for (int i = 0; i < size; i++)
    {
        printf("arr[%d] = %d\n", i, array[i]);
    }
}

int parallel_max(int *array, int size, int rank, int num_procs)
{
    int elements_per_proc = size / num_procs;
    int start = rank * elements_per_proc;
    int end;
    if (rank == num_procs - 1)
    {
        end = size - 1;
    }
    else
    {
        end = start + elements_per_proc - 1;
    }

    int local_max = array[start]; // Инициализируем локальный максимум значением первого элемента

    for (int i = start + 1; i <= end; ++i)
    {
        if (array[i] > local_max)
        {
            local_max = array[i];
        }
    }

    return local_max;
}