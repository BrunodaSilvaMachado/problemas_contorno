#include <stdio.h>
#include <stdlib.h>
#include <linalg.h>

#define N 20
#define DEBUG 1

double p(double x)
{
    return -4/(double)x;
    //return -2.0/(double)x;
}

double q(double x)
{
    return 2.0*pow(x,-2);
}

double r(double x)
{
    return -2*pow(x,-2);
    //return sin(log(x))/(double)pow(x,2);
}

int main()
{

    //double a = 0, alpha = -0.3, b = M_PI_2,beta = -0.1; //condições de contorno
    double a = 1, alpha = 0.5, b = 2,beta = log(2); //condições de contorno
    double h;
    double x;
    double **A, *w ;
    int i;

    h = (b - a)/(double)(N + 1);

    A = (double**)malloc(N * sizeof(double*));

    for(i = 0; i < N;i++)
    {
        A[i] = (double*)malloc((N + 1) * sizeof(double));
    }

	//inicializa valores comuns na matriz
    for(i = 1;i < N - 1; i++)
    {
        x = a + i*h;
		A[i][i+1] = -1 + h/2.0*p(x); // inicializa a diagonal superior
        A[i][i] = 2 + h * h* q(x); // inicializa a diagonal principal
		A[i][i-1] = -1 - h/2.0*p(x); // inicializa a diagonal inferior
    }

	//inicializa a diagonal principal
	A[0][0] = 2 + h * h* q(a);  // (ponto superior fora do laço)
	A[N - 1][N - 1] = 2 + h * h* q(a + (N - 1)*h); //(ponto inferior fora do laço)

	// inicializa a diagonal superior (ponto superior fora do laço)
	A[0][1] = -1 + h/2.0*p(a);

	// inicializa a diagonal inferior (ponto inferior fora do laço)
	A[N - 1][N - 2] = -1 - h/2.0*p(a + (N - 2)*h);

    //linha aumentada

    A[0][N] = -h*h*r(a + h) + (1 + h/2.0*p(a + h))*alpha;
    A[N - 1][N] = -h*h*r(a + N*h) + (1 - h/2.0*p(a + N*h))*beta;

    for(i = 1; i < N - 1; i++)
    {
        A[i][N] = -h*h*r(a + (i + 1)*h);

		#if DEBUG
		printf("%d,%lf\n",i,r(a + (i + 1)*h));
		#endif //DEBUG
    }

    imprimeMatriz(A,N,N+1);
	w = metodoJacobi(A,N,0);

	puts("resultado:");
	for(i = 0; i < N; i++)
	{
		printf("%lf\t%lf\n",a + (i + 1)*h,w[i]);
	}
	puts("\n");

	for(i = 0; i < N; i++)
	{
		free(A[i]);
	}

    return 0;
}























