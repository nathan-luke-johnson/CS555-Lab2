#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/* To Compile: mpicc -g performance.c -o performance
 *           To Execute: mpirun -np 4 MpiHello
 *           */

int main(int argc, char *argv[])
{   
  int myRank, size;
  
  // If there are not enough args, then just quit
  if(argc<3)
  {
    return 1;
  }

  int numArrayElems = atoi(argv[1]);
  int lenArrayElem = atoi(argv[2]);

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (size<2) MPI_Abort(MPI_COMM_WORLD, 1);


  char* sendBuffer = malloc(sizeof(char)*(lenArrayElem*numArrayElems+1));
  char* recvBuffer = malloc(sizeof(char)*(lenArrayElem*numArrayElems+1));
  char* finalBuffer = malloc(sizeof(char)*(lenArrayElem*numArrayElems+1));
  sendBuffer[lenArrayElem*numArrayElems]='\0';
  recvBuffer[lenArrayElem*numArrayElems]='\0';
  finalBuffer[lenArrayElem*numArrayElems]='\0';
  int i,j;
  double startTime = 0.0;
  double endTime = 0.0;
  if (myRank==0)
  {
    //printf("Hello World - I'm the master\n");

    for(i = 0; i < numArrayElems; i++)
    {
      for(j = 0; j < lenArrayElem; j++) 
      {
        sendBuffer[i*lenArrayElem+j] = '0'+i;
      }
    }
   //finalBuffer = malloc(sizeof(char)*lenArrayElem*numArrayElems);
    //printf("sendBuffer: %s\n",sendBuffer);
  }
  
  MPI_Barrier(MPI_COMM_WORLD);
  startTime = MPI_Wtime(); 
  
  for(i = 0; i < numArrayElems*lenArrayElem; i+=lenArrayElem*size)
  {
    MPI_Scatter(
      &sendBuffer[i],
      lenArrayElem,
      MPI_CHAR,
      &recvBuffer[i],
      lenArrayElem,
      MPI_CHAR,
      0,
      MPI_COMM_WORLD);
  }

  for(i = 0; i < numArrayElems*lenArrayElem; i+=lenArrayElem*size)
  {
    MPI_Gather(
      &recvBuffer[i],
      lenArrayElem,
      MPI_CHAR,
      &finalBuffer[i],
      lenArrayElem,
      MPI_CHAR,
      0,
      MPI_COMM_WORLD);
  }
  
  endTime = MPI_Wtime();
  MPI_Barrier(MPI_COMM_WORLD);
  printf("The operation took %f seconds on Processor %d\n", endTime - startTime, myRank);
  // Cleanup step
  free(sendBuffer);
  free(recvBuffer);
  free(finalBuffer);
  MPI_Finalize();
  return 0;
}

