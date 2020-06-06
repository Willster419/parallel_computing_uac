// p7_gather.c
// Generate random values for each process and send to be summed by master
// 

// Includes
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

// Defines
#define VALUES_PER_PROCESS 10

// Gather model of MPI
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
    // use Reduce as barrier and to run simple operation
    //         send_buffer, recieve_buffer, num_elements_per_process, datatype, operation, recieving_process_id, communication_network
    MPI_Reduce(&sum,        NULL,           1,                        MPI_INT,  MPI_SUM,   0,                    MPI_COMM_WORLD);
  }

  if(process_id == 0)
  {
    MPI_Status status;
    int recieve_value;

    // use Reduce as barrier and to run simple operation
    // https://docs.microsoft.com/en-us/message-passing-interface/mpi-reduce-function
    //         send_buffer, recieve_buffer, num_elements_per_process, datatype, operation, recieving_process_id, communication_network
    MPI_Reduce(&sum,        &recieve_value, 1,                        MPI_INT,  MPI_SUM,   0,                    MPI_COMM_WORLD);
    printf("Master process has recieved all values\n");

    printf("The sum of all values is %d\n", recieve_value);
    //printf("la suma de todos los rangos es =%d\n",sum);
  }

  // End the program
  MPI_Finalize();
}