#include <mpi.h> 
#include <stdio.h> 
 
int main(int argc, char** argv) { 
    int rank, size; 
    int data; // The data to broadcast 
 
    MPI_Init(&argc, &argv); // Initialize MPI environment 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process 
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the number of processes 
 
    if (rank == 0) { 
        data = 42; // Root process sets the data 
        printf("Process %d is broadcasting data = %d\n", rank, data); 
    } 
 
    // Broadcast the data from process 0 to all processes 
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD); 
 
    // All processes print the received data 
    printf("Process %d received data = %d\n", rank, data); 
 
    MPI_Finalize(); // Finalize the MPI environment 
    return 0; 
}