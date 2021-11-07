/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <stdio.h>
#include <omp.h>
static long num_steps = 100000000;
double step;
#define NUMS_THREADS 8
int main ()
{
	int i, nthreads;
	double  pi = 0.0;
	double start_time, run_time;
	omp_set_num_threads(NUMS_THREADS);
	start_time = omp_get_wtime();
	#pragma omp parallel
	{
	  int i, id, nthrds;
	  double x, sum = 0.0, step = 1.0/(double) num_steps;
	  id = omp_get_thread_num();	  
	  nthrds = omp_get_num_threads();
	  if(id == 0) nthreads = nthrds;
	  for (i=id;i< num_steps; i = i + nthrds){
		  x = (i+0.5)*step;
		  sum += 4.0/(1.0 + x* x);
	  }

	  #pragma omp critical
	  {
	  pi += sum;
	  }
	}
	  // pi = step * sum;
	  run_time = omp_get_wtime() - start_time;
	  printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi/num_steps,run_time);
}	  





