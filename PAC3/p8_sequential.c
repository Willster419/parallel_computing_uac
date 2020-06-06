#include <stdlib.h>
#include <stdio.h>


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

	int i;
	double n=1000000000.0, a=0.0, b=1.0, h=0.0;
	double result=0.0;

	h = (b-a)/n;
	result = fragment(a, b, n, h);

	printf("Result: %.20ff\n", result);
	
	exit(0);
}
