// p7_send.c
// Generate random values for each process and send to be summed by master
// 

// Includes
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

// Defines
#define VALUES_PER_PROCESS 10

// Send-recieve model of MPI
int main(int argc, char **argv)
{
  // MPI variables
  int total_active_processes;
  int process_id;

  // 1d integer array of total values to sum
  int value_list[VALUES_PER_PROCESS];

  // hold the sum of all the values
  int sum = 0;

  // temp var
  int i;

  // Initialize the MPI system
  MPI_Init(&argc, &argv);

  // the ID of this process
  MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

  //the total number of active processes
  MPI_Comm_size(MPI_COMM_WORLD, &total_active_processes);

  // setup teh variables
  if(process_id == 0)
  {
    printf("There are %d total processes running\n", total_active_processes);
  }

  printf("Process %d is creating %d random values starting from address %x\n", process_id, VALUES_PER_PROCESS, &value_list);
  // seed each process with new random from the address being different
  srand((unsigned int) &value_list);

  // init the array of values
  for (i=0; i<VALUES_PER_PROCESS; i++)
  {
    // create values from 1 to 10
    int random = (rand() % 10) + 1;
    // generate a random value
    //printf("Process %d: Value %d created for index %d\n", process_id, random, i);
    value_list[i] = random;
  }

  //sum the values
  for (i=0; i<VALUES_PER_PROCESS; i++)
  {
    sum += value_list[i];
  }
  printf("Process %d creates value sum %d\n", process_id, sum);

  if(process_id != 0)
  {
    // send the values to the master process via MPI_Send()
    // https://docs.microsoft.com/en-us/message-passing-interface/mpi-send-function
    printf("Process %d sending value to master\n", process_id);
    //MPI_Send(buffer, num_elements, data_type, proc_destination, message_tag, communication_network);
    MPI_Send  (&sum,   1,            MPI_INT,   0,                0,           MPI_COMM_WORLD);
  }

  if(process_id==0)
  {
    // 1d integer array of total values per process
    MPI_Status status;
    int recieve_value;

    // wait for each sub process to send values via MPI_recieve();
    // MPI_recieve();
    // it needs to receive N-1 recieves,
    // https://docs.microsoft.com/en-us/message-passing-interface/mpi-recv-function
    // https://docs.microsoft.com/en-us/message-passing-interface/mpi-status-structure
    for(i = 1; i < total_active_processes-1; i++)
    {
      // recieve in any order from any process
      //       buffer,         num_elements, data type, proc_source,    message_tag, communicator    status (out)
      MPI_Recv(&recieve_value, 1,            MPI_INT,   MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      printf("Recieved value %d from process %d\n", recieve_value, status.MPI_SOURCE);
      sum += recieve_value;
    }

    printf("The sum of all values is %d\n", sum);
    //printf("la suma de todos los rangos es =%d\n",sum);
  }

  // End the program
  MPI_Finalize();
}