#include <mpi.h> 
#include <stdio.h> 
 
int main(int argc, char** argv) { 
    int rank, size, data = 0; 
 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
 
    if (size < 2) { 
        printf("This program requires at least 2 processes.\n"); 
        MPI_Abort(MPI_COMM_WORLD, 1); 
    } 
 
    if (rank == 0) { 
        // Rank 0 sends first, then receives 
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); 
        printf("Process 0 sent data to Process 1\n"); 
 
        MPI_Recv(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        printf("Process 0 received data from Process 1\n"); 
    } else if (rank == 1) { 
        // Rank 1 receives first, then sends 
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        printf("Process 1 received data from Process 0\n"); 
 
        MPI_Send(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
        printf("Process 1 sent data to Process 0\n"); 
    } 
 
    MPI_Finalize(); 
    return 0; 
}