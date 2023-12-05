#include <stdio.h>
#include <omp.h>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    int n = 1000000;
    int mass1[n], mass2[n];
    for (int i = 0; i < n; i++)
    {
        mass1[i] = rand() % 21 - 10;
        mass2[i] = rand() % 21 - 10;
    }

    for (int n_rows = 1; n_rows < 11; n_rows++)
    {
        int sum = 0;
        double start_time = omp_get_wtime();
#pragma omp parallel num_threads(n_rows) reduction (+: sum)
        {
#pragma omp for
            for (int i = 0; i < n; i++)
            {
                int result = mass1[i] * mass2[i];
                sum += result;
            }
        }
        double end_time = omp_get_wtime();
        printf("Зависимость от количества потоков:  %d\n", n_rows);
        printf("Скалярное произведение %d\n", sum);
        printf("Время на замер времени %lf\n", end_time - start_time);
    }
}
