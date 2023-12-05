#include <stdio.h>
#include <omp.h>
using namespace std;

int main(int argc, char *argv[]){
    int sum = 0;
    int mass[10];
    for (int i=0; i<10; i++){
        mass[i]=1;
    }

#pragma omp parallel shared(mass) reduction (+: sum)
{
#pragma omp for 
    for (int i=0; i<10; i++) sum=sum+mass[i];
}
printf("Сумма при первом распараллерировании %d\n", sum);

sum=0;
#pragma omp parallel shared(mass, sum)
{
    int local_sum = 0;
    #pragma omp for
        for (int i = 0; i < 10; ++i) local_sum += mass[i];
    #pragma omp atomic
        sum += local_sum;
}
 printf("Сумма при втором распараллерировании %d\n", sum);

sum=0;
#pragma omp parallel shared(mass, sum)
{
    int local_sum = 0;
    #pragma omp for
    for (int i = 0; i < 10; ++i) local_sum += mass[i];
    #pragma omp critical
{
        sum += local_sum;
    }
}
printf("Сумма при третьем распараллерировании %d\n", sum);
}
