#include <stdio.h>
#include <omp.h>

int main(){
	printf("%d\n", _OPENMP);
	printf("# of procs: %d\n", omp_get_num_procs());
	printf("# of threads: %d\n", omp_get_num_threads());
	omp_set_num_threads(10);
	#pragma omp parallel
	
	{
		//int omp_get_thread_num()
		printf("Hello OpenMP! of threads =%d. Thread ID = %d\n", omp_get_num_threads(), omp_get_thread_num());
	}
	return 0;
}