// Write a MPI Program to demonstration of MPI_Send and MPI_Recv.
#include "mpi.h"
#include <stdio.h>
int main(int argc, char** argv){
  int rank, size;
  int number;
  MPI_Init(&argc, &argv); // Initialize the MPI environment
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process
  MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the number of processes
  if (size < 2) {
    if (rank == 0) {
      printf("This program requires at least two processes.\n");
    }
    MPI_Finalize();
    return 0;
  }
  if (rank == 0){
    number = 100;  //message to send
    printf ("Process 0 sending number %d to process 1\n", number);
    MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); // Send the message to process 1
  }else if (rank == 1){
    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Receive the message from process 0
    printf("Process 1 received number %d from process 0\n", number);
  }
  MPI_Finalize(); // Finalize the MPI environment
  return 0;
}
