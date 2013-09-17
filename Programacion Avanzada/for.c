/* 
 * Uso de OpenMP para hacer un for paralelo. 
 * Ejemplo visto en clase.
 * Para compilar:
 *                 gcc for_paralelo.c -o for_paralelo -fopenmp -lrt
 */

#include <time.h>
#include <stdio.h>
#include <omp.h>

#define TAM 1000000
int a[TAM];

#define NANOSECS_PER_SEC 1000000000

long long a_start() {
    struct timespec s;
    clock_gettime(CLOCK_MONOTONIC, &s);
    return s.tv_sec * NANOSECS_PER_SEC + s.tv_nsec;
}

double a_stop(long long start_time) {
    struct timespec e;
    clock_gettime(CLOCK_MONOTONIC, &e);
    long long end_time = e.tv_sec * NANOSECS_PER_SEC + e.tv_nsec;
    return (double) (end_time - start_time) / NANOSECS_PER_SEC;
}

int fibo(int n) {
    if (n < 2) {
        return n;
    } else {
        return fibo(n - 1) + fibo(n - 2);
    }
}

int main() {
    omp_set_num_threads(2);
    long long inicio = a_start();
    int i;
    #pragma omp parallel for
    for (i = 0; i < TAM; i++) {
        a[i] = fibo(15);
    }
    double time = a_stop(inicio);
    printf("%f\n", time);
    return 0;
}