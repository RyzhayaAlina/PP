#include <stdio.h>
#include <omp.h>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    int n = 10;
    int mass[n];
    for (int i = 0; i < n; i++)
    {
        mass[i] = rand() % 21 - 10;
    }
    for (int n_rows = 1; n_rows < 11; n_rows++)
    {
        int max_element = -20;
        double start_time = omp_get_wtime();
#pragma omp parallel reduction(max : max_element) num_threads(n_rows)
        {
            #pragma omp for
            for (int i = 0; i < n; i++)
            {
                if (mass[i] > max_element)
                {
                    max_element = mass[i];
                }
            }
        }
        double end_time = omp_get_wtime();
        printf("Количество потоков %d и максимум = %d\n", n_rows, max_element);
        printf(" Время на замер времени %lf\n", end_time - start_time);
    }
}