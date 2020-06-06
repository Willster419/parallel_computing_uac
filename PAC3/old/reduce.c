#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 64

int main(argc,argv) 
{
  int MyProc, rank, dest=0, rc, count, tag=1;
  // 1d integer array
  int retval[process_id];

  // 2d
  int retval2[process_id][number_of_values];

  int sum=0;

  MPI_Init(&argc,&argv);

  // the ID of this process
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Comm_size(MPI_COMM_WORLD, &MyProc);

  // MPI_Reduce(&rank, &sum, 1,MPI_INT, MPI_SUM, dest,MPI_COMM_WORLD);

  // if this process is not the master process
  if(rank != 0)
  {
    // each process will add their own values to the master
    // for each value in the array, add it to a master value
    // init the array of values
    for ( i=0; i<SIZE; i++ )
    {
      // generate a random value
      retval[rank][i] = rand();
    }

    // send the values to the master process via MPI_Send()
  }

  //matrixa[0][i] = matrixb[0][i] = rand()*(float)1.1;

	if(rank==0)
	{
	  //printf("la suma de todos los rangos es =%d\n",sum);

    // wait for each sub process to send values via MPI_recieve();
    // MPI_recieve();
    // it needs to receive N-1 recieves, 
    for(int i = 0; i < 6; i++)
    {
      // recieve each one

    }

    // more code after that statement...

	}
	MPI_Finalize();
}