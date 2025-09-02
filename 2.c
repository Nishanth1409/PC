// Write  an  OpenMP  program  that  divides  the  Iterations  into  chunks  containing  2  iterations,respectively  (OMP_SCHEDULE=static,2).  Its  input  should  be  the  number  of  iterations,  and its output should be which iterations of a parallelized for loop are executed by which thread. 
// For example, if there are two threads and four iterations, the output might be the following: 
// a. Thread 0 : Iterations 0 −− 1 
// b. Thread 1 : Iterations 2 −− 3

#include <stdio.h>
#include <omp.h>

int main() {
  int num_iterations;
  printf("Enter the number of iterations: ");
  scanf("%d", &num_iterations);

  #pragma omp parallel
  {
    #pragma omp for schedule(static, 2)
    for (int i = 0; i < num_iterations; i++) {
      printf("Thread %d : Iteration %d\n", omp_get_thread_num(), i);
    }
  }
  return 0;
}