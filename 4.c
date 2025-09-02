// Write a OpenMP program to find the prime numbers from 1 to n employing parallel for  
// directive. Record both serial and parallel execution times.
#include <stdio.h>
#include <omp.h>

int main() {
  int prime[1000], i, j, n;

  // Prompt user to enter the value of n
  printf("In order to find all prime numbers up to n, please enter the value of n: ");
  scanf("%d", &n);


  // Initialize all numbers as prime (set all to 1)
  for (i = 2; i <= n; i++){
    prime[i] = 1;
  }
// i is not a prime number
    prime[i] = 0;
  

  // Sieve of Eratosthenes with Parallelization
  for (i = 2; i * i <= n; i++) {
    if (prime[i]) {
      #pragma omp parallel for private(j) shared(prime, n, i)
      for (j = i * i; j <= n; j += i) {
        prime[j] = 0;
      }
    }
  }

  // Print all prime numbers
  printf("Prime numbers up to %d are:\n", n);
  for (i = 2; i <= n; i++) {
    if (prime[i]==1) {
      printf("%d ", i);
    }
  }
  printf("\n");

  return 0;
}
