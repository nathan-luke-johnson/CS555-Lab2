#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/* To Compile: mpicc -g MpiHello.c -o MpiHello
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


  char* sendBuffer = malloc(sizeof(char)*lenArrayElem*numArrayElems);
  char* recvBuffer = malloc(sizeof(char)*lenArrayElem);
  char* finalBuffer = malloc(sizeof(char)*lenArrayElem*numArrayElems);
  int i,j;

  if (myRank==0)
  {
    //printf("Hello World - I'm the master\n");

    for(i = 0; i < numArrayElems; i++)
    {
      for(j = 0; j < lenArrayElem; j++) 
      {
        sendBuffer[i*lenArrayElem+j] = 'a'+i;
      }
    }
   //finalBuffer = malloc(sizeof(char)*lenArrayElem*numArrayElems);
    //printf("sendBuffer: %s\n",sendBuffer);
  }
  
  double startTime, midTime, endTime;
  startTime = MPI_Wtime();

  MPI_Scatter(
    sendBuffer,
    lenArrayElem,
    MPI_CHAR,
    recvBuffer,
    lenArrayElem,
    MPI_CHAR,
    0,
    MPI_COMM_WORLD);
  
  midTime = MPI_Wtime();
  //printf("Proc %d received %s\n",myRank,recvBuffer);

  MPI_Gather(
    recvBuffer,
    lenArrayElem,
    MPI_CHAR,
    finalBuffer,
    lenArrayElem,
    MPI_CHAR,
    0,
    MPI_COMM_WORLD);
  
  endTime = MPI_Wtime();

  printf("Proc %d scatter time: %f\n",myRank, midTime-startTime);
  printf("Proc %d gather time: %f\n",myRank, endTime-midTime);

  //if(myRank == 0)
  //{
  //  printf("%s\n",finalBuffer);
  //}
  
  // Cleanup step
  free(sendBuffer);
  free(recvBuffer);
  free(finalBuffer);
  MPI_Finalize();
  return 0;
}

