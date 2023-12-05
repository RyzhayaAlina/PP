#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char *argv[])
{
    int n = 1000000;
    int *a=new int[n], *b=new int[n];
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int m = n / size;
    int m1 = n % size;
    if (rank == 0)
    {
        for (int i = 0; i < n; i++)
        {
            a[i] = 1;
            b[i] = 1;
        }
        for (int i = 1; i < size; i++)
        {
            if (i == size - 1)
            {

                MPI_Send(&a[i * (m + m1)], m + m1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Send(&b[i * (m + m1)], m + m1, MPI_INT, i, 1, MPI_COMM_WORLD);
            }
            else
            {

                MPI_Send(&a[i * m], m, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Send(&b[i * m], m, MPI_INT, i, 1, MPI_COMM_WORLD);
            }
        }
        int sum1 = 0;
        for (int i = 0; i < m; i++)
        {
            sum1 += a[i] * b[i];
        }
        int sum2;
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&sum2, 1, MPI_INT, MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &status);
            sum1 += sum2;
        }
        cout << "Скалярное произведение: " << sum1 << endl;
    }
    else if (rank == size - 1)
    {
        int arr1[m + m1], arr2[m + m1];
        MPI_Recv(arr1, m + m1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(arr2, m + m1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        int sum2 = 0;
        for (int i = 0; i < m + m1; i++)
        {
            sum2 += arr1[i] * arr2[i];
        }
        MPI_Send(&sum2, 1, MPI_INT, 0, 3, MPI_COMM_WORLD);
    }

    else
    {
        int message1[m], message2[m];
        MPI_Recv(message1, m, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(message2, m, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        int sum2 = 0;
        for (int i = 0; i < m; i++)
        {
            sum2 += message1[i] * message2[i];
        }
        MPI_Send(&sum2, 1, MPI_INT, 0, 3, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}
