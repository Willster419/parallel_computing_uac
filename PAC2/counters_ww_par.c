
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <memory.h>
#include <malloc.h>
#include <papi.h>

#define SIZE 1000
#define COUNTERS 2

int main(int argc, char **argv) {

  float matrixa[SIZE][SIZE], matrixb[SIZE][SIZE], mresult[SIZE][SIZE];
  int i,j,k;
  int events[COUNTERS] = {PAPI_L1_DCM, PAPI_L2_DCM};
  //int events[COUNTERS] = {PAPI_L3_TCM, PAPI_FP_OPS};
  int ret;
  long long values[COUNTERS];

  //does the system have enough counters in hardware?
  if (PAPI_num_counters() < COUNTERS) {
    fprintf(stderr, "No hardware counters here, or PAPI not supported.\n");
    exit(1);
  }

  //define what each counter should listen to and start them
  if ((ret = PAPI_start_counters(events, COUNTERS)) != PAPI_OK) {
    fprintf(stderr, "PAPI failed to start counters: %s\n", PAPI_strerror(ret));
    exit(1);
  }

  /* Initialize the Matrix arrays */
  for ( i=0; i<SIZE*SIZE; i++ ){
    mresult[0][i] = 0.0;
    matrixa[0][i] = matrixb[0][i] = rand()*(float)1.1; }

  /* Matrix-Matrix multiply */
  #pragma omp parallel for private (i,j,k) shared (mresult, matrixa, matrixb) schedule (static)
  for (i=0;i<SIZE;i++)
   for(j=0;j<SIZE;j++)
    for(k=0;k<SIZE;k++)
      mresult[i][j]=mresult[i][j] + matrixa[i][k]*matrixb[k][j];

  //read the values from the counters
  if ((ret = PAPI_read_counters(values, COUNTERS)) != PAPI_OK) {
    fprintf(stderr, "PAPI failed to read counters: %s\n", PAPI_strerror(ret));
    exit(1);
  }

  //printf("Total hardware flops  = %lld\n",values[1]);
  printf("Total L1 cache misses = %lld\n",values[0]);
  printf("Total L2 cache misses = %lld\n",values[1]);
  //printf("Total L3 cache misses = %lld\n",values[0]);

  exit(0);
}
