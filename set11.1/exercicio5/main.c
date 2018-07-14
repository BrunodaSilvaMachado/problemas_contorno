#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define TAM 2

double p(double x) //y'
{
    //return -2.0/x;
    return 0;
}

double q(double x)//y
{
    //return 2.0/(double)pow(x,2);
    return 100;
}

double r(double x)//x
{
    //return sin(log(x))/(double)pow(x,2);
    return 0;
}

double shootingLinear(char *filename,double a, double b,int n,double alfa,double beta)
{
    FILE *arq = fopen(filename,"w");
    double h,x;
    ///runge-kutta
    double k1[TAM],k2[TAM],k3[TAM],k4[TAM];
    ///diff runge-kutta
    double dk1[TAM],dk2[TAM],dk3[TAM],dk4[TAM];
    ///u e v
    double *u1 = (double*)malloc(n * sizeof(double)),
            *u2= (double*)malloc(n * sizeof(double)),
            *v1= (double*)malloc(n * sizeof(double)),
            *v2= (double*)malloc(n * sizeof(double));
    double _w1,_w2,w1,w2;
    int i;

    h = (b - a)/(double)n;
    u1[0] = alfa;
    u2[0] = 0;
    v1[0] = 0;
    v2[0] = 1;

    ///runge-kutta
    for(i = 0; i <= n - 1; i++)
    {
        x = a + i*h;
        k1[0] = h*u2[i];
        k1[1] = h*(p(x)*u2[i] + q(x)*u1[i]+r(x));
        k2[0] = h*(u2[i] + 0.5*k1[1]);
        k2[1] = h*(p(x+h/2.0)*(u2[i] + 0.5*k1[1]) + q(x+h/2.0)*(u1[i]+0.5*k1[0])+r(x+h/2.0));
        k3[0] = h*(u2[i]+0.5*k2[1]);
        k3[1] = h*(p(x+h/2.0)*(u2[i]+0.5*k2[1]) + q(x+h/2.0)*(u1[i]+0.5*k2[0])+r(x+h/2.0));
        k4[0] = h*(u2[i]+k3[1]);
        k4[1] = h*(p(x+h)*(u2[i]+k3[1]) + q(x+h)*(u1[i]+k3[0])+r(x+h));
        u1[i+1] = u1[i] + (1/6.0)*(k1[0]+2*k2[0]+2*k3[0]+k4[0]);
        u2[i+1] = u2[i] + (1/6.0)*(k1[1]+2*k2[1]+2*k3[1]+k4[1]);

        dk1[0] = h*v2[i];
        dk1[1] = h*(p(x)*v2[i] + q(x)*v1[i]);
        dk2[0] = h*(v2[i] + 0.5*dk1[1]);
        dk2[1] = h*(p(x+h/2.0)*(v2[i]+0.5*dk1[1])+q(x+h/2.0)*(v1[i] + 0.5*dk1[0]));
        dk3[0] = h*(v2[i] + 0.5*dk2[1]);
        dk3[1] = h*(p(x+h/2.0)*(v2[i]+0.5*dk2[1])+q(x+h/2.0)*(v1[i] + 0.5*dk2[0]));
        dk4[0] = h*(v2[i] + dk3[1]);
        dk4[1] = h*(p(x+h)*(v2[i]+dk3[1])+q(x+h)*(v1[i] + dk3[0]));

        v1[i+1] = v1[i] + (1/6.0)*(dk1[0]+2*dk2[0]+2*dk3[0]+dk4[0]);
        v2[i+1] = v2[i] + (1/6.0)*(dk1[1]+2*dk2[1]+2*dk3[1]+dk4[1]);
    }

    ///shooting linear
    _w1 = alfa;
    _w2 = (beta - u1[n])/(double)v1[n];

    //printf("linha1\n");
    puts("x_i \t u_i \t v_i \t w1 \t w2");
    printf("%lf,%lf,%lf,%lf,%lf\n",a,u1[0],v1[0],_w1,_w2);
    fprintf(arq,"%.16lf\t%.16lf\t%.16lf\n",a,_w1,_w2);

    for(i = 1; i <= n;i++)
    {
        w1 = u1[i]+_w2*v1[i];
        w2 = u2[i]+_w2*v2[i];
        x = a + i*h;
        //printf("linha2\n");
        printf("%lf,%lf,%lf,%lf,%lf\n",x,u1[i],v1[i],w1,w2);
        fprintf(arq,"%.16lf\t%.16lf\t%.16lf\n",x,w1,w2);
    }

    fclose(arq);
    return 0;
}

int main()
{
    printf("t1\n");
    shootingLinear("dados3.txt",0,1,10,1,exp(-10));
    printf("t2\n");
    shootingLinear("dados4.txt",0,1,20,1,exp(-10));
    return 0;
}
