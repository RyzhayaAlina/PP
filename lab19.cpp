#include <cstdlib>
#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // инициализация матрицы каждым процессом
    int N = 10, i, j, k;
    int A[N][N], B[N][N], C[N][N];
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            A[i][j] = B[i][j] = 1;

    MPI_Barrier(MPI_COMM_WORLD); // барьерная синхронизация процессов

    // начало замера времени для каждого процесса
    double time_start = MPI_Wtime();
    // перемножение матриц
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    // конец замера времени
    double time_finish = MPI_Wtime();
    // вывод время выполнения перемножения матриц на каждом процессе
    cout << rank << " time = " << time_finish - time_start << endl;
    MPI_Finalize();
}