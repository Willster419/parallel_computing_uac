#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>


double f(double x)
{
	return(4.0/(1.0+x*x));
}


double fragment(double a, double b, double num_fragments, double h)
{
	double est, x;
	int i;

 	est = (f(a) + f(b))/2.0;
	for (i=1; i<=num_fragments-1; i++){
		x = a + i*h;
		est += f(x);
		}
	est = est*h;

	return est;	
}

int main(int argc, char **argv) {
	
	int i, MyProc, size, j=0, tag=50;
	double total;
	double n=1000000000.0, a=0.0, b=1.0, h=0.0;
	double result=0.0;
	
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&MyProc);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	
	h = (b-a)/n;
	result = fragment(a, b, n, h);
	

	if(MyProc==0){
		total=result;
		for (i=1; i<size;i++){
		MPI_Recv(&result,1,MPI_DOUBLE,i,tag,MPI_COMM_WORLD,&status);
			total=total+result;
		}
			printf("Valor Integral: %.20ff\n", total);
	}
	else{
		MPI_Send(&result,1,MPI_DOUBLE,j,tag,MPI_COMM_WORLD);
		
	}
			
	MPI_Finalize();
}
