#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char **argv)
{
    int rank, size, prev, next;
    int buf[2];
    MPI_Init(&argc, &argv);
    MPI_Request reqs[4];
    MPI_Status stats[4];
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    prev = rank - 1;
    next = rank + 1;

    if (rank == 0)
        prev = size - 1;
    if (rank == size - 1)
        next = 0;

    MPI_Sendrecv(&rank, 1, MPI_INT, next, 1, &buf[0], 1, MPI_INT, prev, 1, MPI_COMM_WORLD, &stats[0]);
    MPI_Sendrecv(&rank, 1, MPI_INT, prev, 2, &buf[1], 1, MPI_INT, next, 2, MPI_COMM_WORLD, &stats[1]);

    // сообщение, число, тип данных, куда, тэг
    // сообщение, число, тип данных, откуда, тэг
    // Здесь необходимо вывести на экран номер текущего процесса, и что он получает от предыдущего и следующего процессов.
    cout<<"Номер текущего процесса:"<<rank<<" Сообщение от предыдущего процесса "<<buf[0]<<" Сообщение от следующего процесса "<<buf[1]<<endl;
    MPI_Finalize();
}