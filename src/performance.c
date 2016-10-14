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
  if(numArrayElems < 1) { return 1; }
  if(lenArrayElem < 1) { return 1; }

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (size<2) MPI_Abort(MPI_COMM_WORLD, 1);


  char* sendBuffer = (char*) malloc(sizeof(char)*(lenArrayElem*numArrayElems+1));
  sendBuffer[lenArrayElem*numArrayElems]='\0';
  char* recvBuffer = (char*) malloc(sizeof(char)*(lenArrayElem*numArrayElems+1));
  recvBuffer[lenArrayElem*numArrayElems]='\0';
  int i,j;

  if (myRank==0)
  {
    double startTime, endTime;
    //printf("Hello World - I'm the master\n");
    for(i = 0; i < numArrayElems; i++)
    {
      for(j = 0; j < lenArrayElem; j++)
      {
        sendBuffer[i*lenArrayElem+j] = 'a' + i;
      }
    }

    startTime = MPI_Wtime();
    
    for(i = 0; i < numArrayElems; i++)
    {
      MPI_Send(
        &(sendBuffer[lenArrayElem*i]),
        lenArrayElem,
        MPI_CHAR,
        1,
        0,
        MPI_COMM_WORLD);
    }
    for(i = 0; i < numArrayElems; i++)
    { 
      MPI_Recv(
        &(recvBuffer[lenArrayElem*i]),
        lenArrayElem,
        MPI_CHAR,
        1,
        0,
        MPI_COMM_WORLD,
        MPI_STATUS_IGNORE);
    }
    endTime = MPI_Wtime();
    printf("The operation took %f seconds.\n", endTime - startTime);
    //printf("Sent %s, and received %s\n",sendBuffer, recvBuffer);
  }
  
  else //myRank == 
  {
    for(i = 0; i < numArrayElems; i++)
    {
      MPI_Recv(
        &(recvBuffer[lenArrayElem*i]),
        lenArrayElem,
        MPI_CHAR,
        0,
        0,
        MPI_COMM_WORLD,
        MPI_STATUS_IGNORE);
    }
    for(i = 0; i < numArrayElems; i++)
    {
      MPI_Send(
        &(recvBuffer[lenArrayElem*i]),
        lenArrayElem,
        MPI_CHAR,
        0,
        0,
        MPI_COMM_WORLD);
    }
  }

  free(sendBuffer);
  free(recvBuffer);
  MPI_Finalize();
  return 0;
}

