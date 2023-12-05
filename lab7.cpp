#include <stdio.h>
#include <omp.h>
#include <iostream>
using namespace std;

double func_cvad(double x)
{
    return (4.0 / (1.0 + x * x));
}

int main()
{   
    omp_set_num_threads(1);
    double inverse_N, x, pi;
    int N;
    printf("Введите желаемую точность: \n");
    scanf("%d", &N);
    printf("Количество нитей - 1\n");
    inverse_N = 1.0 / N;
    pi = 0.0;
    double start_time = omp_get_wtime();
#pragma omp parallel for private(x) shared(inverse_N) reduction(+ : pi)
    for (int i = 0; i < N; i++)
    {
        x = inverse_N * (i + 0.5);
        pi = pi + func_cvad(x);
    }
    double pi_finish = inverse_N * pi;
    printf("pi = %f\n", pi_finish);
    double end_time = omp_get_wtime();
    printf("Время на замер времени %lf\n", end_time - start_time);
}
// 1 нить 1000
// pi = 3.141593
// Время на замер времени 0.000038

// 1000
// pi = 3.141593
// Время на замер времени 0.000247