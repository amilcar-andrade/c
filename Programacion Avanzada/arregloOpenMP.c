#include <stdio.h>
#include <omp.h>
#include <time.h>
#define TAM 1000000
#define NANOSEC_PER_SEC 1000000000


int a[TAM];

long start(){
       struct timespec s;
       clock_gettime(CLOCK_MONOTONIC, &s);
       return s.tv_sec * NANOSEC_PER_SEC + s.tv_nsec;
}

double stop(long long start_time){
       struct timespec e;
       clock_gettime(CLOCK_MONOTONIC, &e);
       long long end_time = e.tv_sec * NANOSEC_PER_SEC + e.tv_nsec;        
       return (double)(end_time - start_time)/NANOSEC_PER_SEC;
}


int fibo (int n){
       if(n<2){
               return n;
       }else{
               return fibo(n-1)+fibo(n-2);
       }
}

int main(){
       int i = 0;
       omp_set_num_threads(1);
       long long inicio = start();
       #pragma omp parallel for
       for(i = 0; i<TAM; i++){
               a[i] = fibo(20);
       }
       double time = stop(inicio);
       printf("%f\n", time);
       return 0;
}