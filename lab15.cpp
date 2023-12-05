#include <iostream>
#include "mpi.h"
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
    int n = 1000000;
    int *a = new int[n];
    int *b = new int[n];
    int rank, size;
    double time_start, time_finish;
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int k = size;
    for (int i = 0; i < n; i++)
    {
        a[i] = 1;
    }

    time_start = MPI_Wtime();
    while (k >= 1)
    {
        k /= 2; // 0 1 2 3 4 5 6 7 8 // 4 7 // 0 1 2 3 4 // 2 // 0 1 // 1
        if (rank < k)
        {
            MPI_Recv(b, n, MPI_INT, MPI_ANY_SOURCE, 5, MPI_COMM_WORLD, &status);
            for (int i = 0; i < n; i++)
            {
                a[i] += b[i];
            }
        }
        else if (rank < k * 2)
        {
            MPI_Send(a, n, MPI_INT, (rank - k), 5, MPI_COMM_WORLD);
            break;
        }
    }

    if (rank == 0)
    {
        time_finish = MPI_Wtime();
        cout << "time = " << (time_finish - time_start) << endl;
        for (int j = 0; j < 5; j++)
        {
            cout << "Элементы массива при делении на 2: " << a[j] << endl;
        }
    }

    for (int i = 0; i < n; i++)
    {
        a[i] = 1;
    }

    time_start = MPI_Wtime();

    MPI_Reduce(a, b, n, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    time_finish = MPI_Wtime();
    if (rank == 0)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << "Элементы массива при встроенной функции: " << b[j] << endl;
        }

        cout << "time = " << (time_finish - time_start) << endl;
    }

    MPI_Finalize();
}