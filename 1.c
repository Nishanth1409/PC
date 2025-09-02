// Write  a  OpenMP  program  to  sort  an  array  on  n  elements  using  both  sequential  and  parallel mergesort(using  Section). Record the difference in execution time.
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int* arr, int I, int m, int r) {
  int i, j, k;
  int n1 = m - I + 1;
  int n2 = r - m;
  int* L = (int*)malloc(n1 * sizeof(int));
  int* R = (int*)malloc(n2 * sizeof(int));
  for (i = 0; i < n1; i++) L[i] = arr[I + i];
  for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
  i = 0; j = 0; k = I;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) arr[k++] = L[i++];
    else arr[k++] = R[j++];
  }
  while (i < n1) arr[k++] = L[i++];
  while (j < n2) arr[k++] = R[j++];
  free(L);
  free(R);
}

// Sequential mergesort function
void sequentialMergeSort(int* arr, int I, int r) {
  if (I < r) {
    int m = I + (r - I) / 2;
    sequentialMergeSort(arr, I, m);
    sequentialMergeSort(arr, m + 1, r);
    merge(arr, I, m, r);
  }
}

// Parallel mergesort function
void parallelMergeSort(int* arr, int I, int r, int depth) {
  if (I < r) {
    int m = I + (r - I) / 2;
    if (depth <= 0) {
      sequentialMergeSort(arr, I, m);
      sequentialMergeSort(arr, m + 1, r);
    } else {
      #pragma omp parallel sections
      {
        #pragma omp section
        parallelMergeSort(arr, I, m, depth - 1);

        #pragma omp section
        parallelMergeSort(arr, m + 1, r, depth - 1);
      }
    }
    merge(arr, I, m, r);
  }
}

// check if the array is sorted
int isSorted(int* arr, int n) {
  for (int i = 1; i < n; i++) {
    if (arr[i - 1] > arr[i]) return 0;
  }
  return 1;
}

// Main function
int main() {
  int n = 1000000;
  int* arrseq = (int*)malloc(n * sizeof(int));
  int* arrpar = (int*)malloc(n * sizeof(int));
  srand(42);
  for (int i = 0; i < n; i++) {
    arrseq[i] = rand() % 1000000;
    arrpar[i] = arrseq[i];
  }

  // Time sequential mergesort
  double start_seq = omp_get_wtime();
  sequentialMergeSort(arrseq, 0, n - 1);
  double end_seq = omp_get_wtime();

  // Time parallel mergesort
  double start_par = omp_get_wtime();
  parallelMergeSort(arrpar, 0, n - 1, 10);
  double end_par = omp_get_wtime();

  // Check if the arrays are sorted
  if (isSorted(arrseq, n) && isSorted(arrpar, n)) {
    printf("Arrays are sorted\n");
    printf("Sequential mergesort time: %f\n", end_seq - start_seq);
    printf("Parallel mergesort time: %f\n", end_par - start_par);
  } else {
    printf("Arrays are not sorted\n");
  }
  free(arrseq);
  free(arrpar);
  return 0;
}