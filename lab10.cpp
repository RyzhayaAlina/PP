#include <iostream>
#include "mpi.h"

// вариант 13

using namespace std;
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    double time_start, time_finish;
    int rank, n, message;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    time_start = MPI_Wtime();
        if (rank == 0){
            MPI_Send(&rank, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        }
        else if (rank==n-1) {
            MPI_Recv(&message, 1, MPI_INT, rank-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            cout << "Hello from process " << message << endl;
            time_finish = MPI_Wtime();
            cout << "time = " << (time_finish-time_start) << endl;
        }
        else
        {
            MPI_Recv(&message, 1, MPI_INT, rank-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            cout << "Hello from process " << message << endl;
            MPI_Send(&message, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        }
    MPI_Finalize();
    return 0;
}