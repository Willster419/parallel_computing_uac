#include <stdio.h>

const int blocksize = 4;
const int N=10;
const int periodos=10;

__global__
void moving_average(float *DATA, float *MOV, float *valores)
{
  int i=blockIdx.x*blockDim.x + threadIdx.x, 
  int j=blockIdx.y*blockDim.y + threadIdx.y;
  
  float sum;
  
  for(j=0;j<sizeN-1;j++) {
    sum = 0;
    for(i=0;i<periods;i++) {
      sum += valores[i]
    }
    DATA[i]= sum/periodos;
  }

  for(j==N-1;j++) {
    sum = 0;
    for(i=0;i<N;i++) {
      sum += valores[i]
    }
    MOV[i]= sum/N;
  }
}

int main()
{
  float *DATA_d, *MOV_d;
  int bytes = N*sizeof(float);

  cudaMalloc((void**) &DATA_d, bytes);
  cudaMalloc((void**) &MOV_d, bytes);
  cudaMemcpy(DATA_d, valores, N*sizeof(float), cudaMemcpyHostToDevice);
  
  dim3 dimBlock( blocksize, 1 );
  dim3 dimGrid( 1, 1 );
  mavg_device<<<grids, blocks>>> (N, DATA_d, periodos, MOV_d);

  cudaMemcpy((void*)out,(void*)MOV_d,bytes,cudaMemcpyDeviceToHost);
  cudaFree(DATA_d);
  cudaFree(MOV_d);

  if(j==N; j++){
    printf("Elemento i = %d j = %d, con Promedio %dn", i, j,MOV[i]);
  }
  else{
    for (j=0; j<N; j++)
      printf("Elementos i = %d j = %d, con Promedio móvil %dn", i, j,DATA[i]);
  }

  return EXIT_SUCCESS;
}