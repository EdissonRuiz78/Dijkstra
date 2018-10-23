#include <stdio.h>
#include <omp.h>

//export OMP_NUM_THREADS=4
//to compile gcc -fopenmp filename
//./a.out

static long num_steps = 100000000;
double step;
#define NUM_THREADS 2

void main()
{
    double pi, x, time0, time1, res, sum = 0.0;
    step = 1.0/(double)num_steps;
    
    time0 = omp_get_wtime();
    for(int i = 0; i < num_steps; i++){
        x = (i + 0.5)*step;
        sum = sum + 4.0/(1.0 + x*x);
    }
    pi = step*sum;
    time1 = omp_get_wtime();
    res = time1 - time0;
    printf("Elapse time (%f)\n", res);
    printf("PI value (%f)\n", pi);
}