#include <stdio.h> 
#include <mpi.h> 
 
int main(int argc, char** argv) { 
    int rank, size; 
    int send_data[4] = {10, 20, 30, 40};  // Only root (rank 0) uses this fully 
    int recv_data; 
 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
 
    // Scatter 1 int from root to all processes 
    MPI_Scatter(send_data, 1, MPI_INT, &recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD); 
 
    printf("Process %d received: %d\n", rank, recv_data); 
 
    // Each process increments its value 
    recv_data += 1; 
 
    // Gather updated values at root 
    MPI_Gather(&recv_data, 1, MPI_INT, send_data, 1, MPI_INT, 0, MPI_COMM_WORLD); 
 
    // Root prints the gathered result 
    if (rank == 0) { 
        printf("Gathered data: "); 
        for (int i = 0; i < size; i++) 
            printf("%d ", send_data[i]); 
        printf("\n"); 
    } 
 
    MPI_Finalize(); 
    return 0; 
}