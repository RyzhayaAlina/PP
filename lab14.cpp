#include <iostream>
#include "mpi.h"
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
    int n = 1000000000, N = 10;
    int *a = new int[n];
    int rank, size;
    double time_start, time_finish;
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    for (int i = 1; i <= n; i *= 10)
    {
        time_start = MPI_Wtime();
        for (int j = 0; j < N; j++)
        {
            if (rank == 0)
            {
                MPI_Send(a, i, MPI_INT, 1, 5, MPI_COMM_WORLD);
                MPI_Recv(a, i, MPI_INT, 1, 5, MPI_COMM_WORLD, &status);
            }
            else if (rank == 1)
            {
                MPI_Recv(a, i, MPI_INT, 0, 5, MPI_COMM_WORLD, &status);
                MPI_Send(a, i, MPI_INT, 0, 5, MPI_COMM_WORLD);
            }
        }
        if (rank == 0)
        {
            time_finish = MPI_Wtime();
            auto L = i * sizeof(int);
            double T = (time_finish - time_start) / N;
            auto R = ((2 * N * L) / T) * pow(1024, -2); // перевод в мб
            cout << "Количество байтов: " << L << endl;
            // cout << "Усредненное время: " << T << endl;
            cout << "Пропускная способность: " << R << endl;
        }
    }

    time_start = MPI_Wtime();
    for (int j = 0; j < N; j++)
    {
        if (rank == 0)
        {
            MPI_Send(NULL, 0, MPI_INT, 1, 5, MPI_COMM_WORLD);
            MPI_Recv(NULL, 0, MPI_INT, 1, 5, MPI_COMM_WORLD, &status);
        }
        else if (rank == 1)
        {
            MPI_Recv(NULL, 0, MPI_INT, 0, 5, MPI_COMM_WORLD, &status);
            MPI_Send(NULL, 0, MPI_INT, 0, 5, MPI_COMM_WORLD);
        }
    }
    if (rank == 0)
    {
        time_finish = MPI_Wtime();
        double T = (time_finish - time_start) / N;
        auto s = T/(2*N);
        cout << "Латентность: " << s << endl;
    }
    MPI_Finalize();
}