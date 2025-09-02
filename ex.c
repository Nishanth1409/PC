#include <stdio.h>
#include <omp.h>
int main() {
  #pragma omp parallel
  {
    #pragma omp critical
    {
      printf("Hello world\n");
    }
  }
  return 0;
}