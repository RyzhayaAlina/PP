#include <stdio.h>
#include <omp.h>
#include <iostream>
using namespace std;

int main()
{
    int N = 5;
    int A[N][N], B[N][N], C[N][N];
    double t, t1, t2;
    int i, j, k;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            A[i][j] = B[i][j] = i * j;
    for (int n_rows = 1; n_rows < 11; n_rows++)
    {
        double t1 = omp_get_wtime();
#pragma omp parallel shared(A, B, C) private(i, j, k) num_threads(n_rows)
        {
#pragma omp for
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < N; j++)
                {
                    C[i][j] = 0;
                    for (k = 0; k < N; k++)
// #pragma omp atomic
                        C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        t2 = omp_get_wtime();
        // t += t2-t1;
        for (i = 0; i < N; i++, putchar('\n'))
        {
            for (j = 0; j < N; j++)
            {
                printf(" %d", C[i][j]);
            }
        }
        printf("Количество нитей =%d\n", n_rows);
        printf("Время нитей =%lf\n", t2 - t1);
        // printf("Эффективность =%lf\n", (t2 - t1) / t);
    }
}