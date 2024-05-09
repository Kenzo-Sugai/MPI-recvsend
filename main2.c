// PRIMEIRA SOLUCAO: VETOR SENDO ENVIADO POR MPI_SEND

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int lock = 0;

void fillVector(float vetor[], int world_size){
    for(int i = 0; i < world_size; i++){
        vetor[i] = (float)rand()/(float)(RAND_MAX/100.0);
    }
}

int main(int argc, char** argv) {
    
    MPI_Init(NULL, NULL);

    int world_size, world_rank;

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    srand(time(NULL));

     if(world_rank == 0){

        printf("RANK 0\n");
        
        float vetor[world_size];

        fillVector(vetor, world_size);

        printf("vetor: ");
        for(int i = 0; i < world_size; i++){
            printf("%.1f ", vetor[i]);
        }
        printf("\n");

        for(int i = 0; i < world_size; i++){
            MPI_Send(vetor, world_size, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
        }
    }

    float vetor[world_size];
   
    MPI_Recv(vetor, world_size, MPI_FLOAT, 0, world_rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("RANK %d\n", world_rank);
    for(int i =0; i < world_size; i++){
        printf("%.1f\n", vetor[i]);
    }
    printf("\n");

    
    MPI_Finalize();
}
