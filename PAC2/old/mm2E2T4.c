
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <memory.h>
#include <malloc.h>
#include <string.h>
#include <omp.h>

//#define SIZE 500

/*
TO RUN:
" ./mm2E2T4 <array_size> <num_threads>"
EXAMPLE:
" ./mm2E2T4 500 4"
*/

int main(int argc, char* argv[]) {

  float **matrixa;
  float **matrixb;
  float **mresult;
  int i,j,k;
  int ARRAY_SIZE;
  int num_threads;
  
  //set ARRAY_SIZE to the provided argument
  //https://github.com/Willster419/ELEC3499_OS_Systems/blob/master/lab9/lab9.c#L67 (my code)
  if(argv[1] != NULL){
    ARRAY_SIZE = atoi(argv[1]);
    printf("DEBUG: ARRAY_SIZE: %d\n",ARRAY_SIZE);
  }
  else{
    printf("ERROR: ARRAY_SIZE argument not suplied!\n");
    return(-1);
  }
  
  //set num_threads to the provided argument
  if(argv[2] != NULL){
    num_threads = atoi(argv[2]);
    printf("DEBUG: num_threads: %d\n",num_threads);
  }
  else{
    printf("ERROR: num_threads argument not suplied!\n");
    return(-1);
  }
  
  //allocate dimension 1
  //https://stackoverflow.com/questions/7221981/how-to-make-a-dynamic-sized-array-in-c
  //https://github.com/Willster419/ELEC3499_OS_Systems/blob/master/lab9/lab9.c#L99
  matrixa = malloc(sizeof(float)*ARRAY_SIZE);
  matrixb = malloc(sizeof(float)*ARRAY_SIZE);
  mresult = malloc(sizeof(float)*ARRAY_SIZE);
  
  //allocate dimension 2
  for(int i = 0; i < ARRAY_SIZE; i++){
    matrixa[i] = malloc(sizeof(float)*ARRAY_SIZE);
    matrixb[i] = malloc(sizeof(float)*ARRAY_SIZE);
    mresult[i] = malloc(sizeof(float)*ARRAY_SIZE);
  }

  /* Initialize the Matrix arrays */
  for ( i=0; i<ARRAY_SIZE*ARRAY_SIZE; i++ ){
    mresult[0][i] = 0.0;
    matrixa[0][i] = matrixb[0][i] = rand()*(float)1.1;
  }
  
  omp_set_num_threads(num_threads);
  
#pragma omp parallel shared(mresult,matrixa,matrixb)private(i,j,k)
{
  /* Matrix-Matrix multiply */
  #pragma omp for schedule (static) nowait
  
  for (k=0;k<ARRAY_SIZE;k++){
   for(j=0;j<ARRAY_SIZE;j++){
    for(i=0;i<ARRAY_SIZE;i++){
      mresult[i][j]=mresult[i][j] + matrixa[i][k]*matrixb[k][j];
    }
   }
  }
}

  exit(0);
}
