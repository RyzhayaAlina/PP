#include <stdio.h>
#include <omp.h>
using namespace std;

int main(int argc, char *argv[]){
// #ifdef _OPENMP
//     cout<<("OpenMP is supported!\n")<<endl;
// #endif
omp_set_num_threads(4);

printf("Последовательная область (1)\n");

#pragma omp parallel num_threads(5)
    {
        int count, num;
        count=omp_get_num_threads(); 
        num=omp_get_thread_num();
        if (num == 0) printf("Всего нитей: %d\n", count);
        else printf("Нить номер %d\n", num);
        printf("Параллельная область (1)\n");
    }

printf("Параллельная область (2)\n");

#pragma omp parallel num_threads(3)
    {   
        int count, num;
        count=omp_get_num_threads(); 
        num=omp_get_thread_num();
        if (num == 0) printf("Всего нитей: %d\n", count);
        else printf("Нить номер %d\n", num);
        printf("Параллельная область (2)\n");
    }
  
printf("Последовательная область (3)\n");
#pragma omp parallel
    {   
        int count, num;       
        count=omp_get_num_threads(); 
        num=omp_get_thread_num();
        if (num == 0) printf("Всего нитей: %d\n", count);
        else printf("Нить номер %d\n", num);
        printf("Параллельная область номер(3)\n");
        
    }
}