#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    
    MPI_Init(NULL, NULL);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    srand(time(NULL));

    if(world_rank == 0){
        
        float vetor[world_size];

        for(int i = 0; i < world_size; i++){
            vetor[i] = float(rand() % 10);
        } 

        for(int i = 0; i < world_size; i++){
            MPI_Send(vetor, sizeof(vetor), MPI_FLOAT, i, 0, MPI_COMM_WORLD);
        }
    }

    
    MPI_Finalize();
}
