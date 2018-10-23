#include <stdio.h>
#include <omp.h>

//export OMP_NUM_THREADS=4
//to compile gcc -fopenmp filename
//./a.out

static long num_steps = 100000000;
double step;
#define NUM_THREADS 4

void main()
{
    int nthreads;
    double pi = 0.0, time0, time1, res;
    step = 1.0/(double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    
    time0 = omp_get_wtime();
    #pragma omp parallel
    {
    int i, id, nthrds;
    double x, sum;
    id = omp_get_thread_num();
    nthrds = omp_get_num_threads();
    if (id == 0) nthreads = nthrds;
    for(i = id, sum=0.0; i < num_steps; i += nthreads){
        x = (i + 0.5)*step;
        sum += 4.0/(1.0 + x*x);
    }
    sum = sum*step;
    #pragma omp atomic
        pi += sum;
    }
    time1 = omp_get_wtime();
    res = time1 - time0;
    printf("Elapse time (%f)\n", res);
    printf("PI value (%f)\n", pi);
}