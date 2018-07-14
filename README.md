# problemas_contorno

  Em matemática, no ramo de equações diferenciais, um problema de valor sobre o contorno é um sistema de equações diferenciais provido de um conjunto de restrições adicionais, as chamadas condições de contorno ou condições de fronteira. Uma solução para um problema de valor sobre o contorno é a solução do sistema de equações diferenciais que satisfaz as condições de contorno.

# Shooting Linear

  Considere o problema de valor de contorno, que desejamos encontrar a solução numérica no intervalo [a,b],

> y" = p(x)y' + q(x)y + r(x) , x ∈ ]a,b]  
> y(a) = α  
> y(b) = β  


  Se p(x) e q(x) e r(x) são continuas em [a,b] e se q(x) > 0 para todo x ∈ [a,b] então o (PVF) acima tem uma unica solução

  O método do shooting consiste em tomar dois problemas de valor inicial (PVI) associados ao (PVF)
os dois PVIs são dados por

>> (PVI_1)  
> y" = p(x)y' + q(x)y + r(x) , x ∈ ]a,b]  
> y(a) = α  
> y'(a) = 0  

e  

>> (PVI_2)  
> y" = p(x)y' + q(x)y + r(x) , x ∈ ]a,b]  
> y(a) = 0  
> y'(a) = 1

  Note que nestes problemas, as equações são as mesmas, mas as condições iniciais são diferentes.
Os problemas (PVI_1) e (PVI_2) possuem cada um uma unica solução. Sejam y_1(x) a solução de (PVI-1)
e y_2(x) a solução de (PVI_2).
Uma conta fácil mostra que    
![eq:shootingLinear](displaymath/shootinglinear.png)
  
  e solução do (PVF). Como a sua solução é unica, então está é a solução do (PVF).
Assim, o método do shooting é baseado na substituição do (PVF) por dois problemas de valor inicial
(PVI-1) e (PVI-2). Sabemos resolver numericamnte os dois problemas e neste trabalho usamos os Métodos de Runge-Kutta.

## Codigo

``` c
double p(double x) //y'
{
  return 0;
}

double q(double x)//y
{
  return 4;
}

double r(double x)//x
{
  return -4*x;
}

double shootingLinear(char *filename,double a, double b,int n,double alfa,double beta)
{
  FILE *arq = fopen(filename,"w");
  double h,x;
  ///runge-kutta chute 1
  double k1[TAM],k2[TAM],k3[TAM],k4[TAM];
  ///runge-kutta chute 2
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

  puts("x_i \t u_i \t v_i \t w1 \t w2");
  printf("%lf,%lf,%lf,%lf,%lf\n",a,u1[0],v1[0],_w1,_w2);
  fprintf(arq,"%lf\t%lf\t%lf\n",a,_w1,_w2);

  for(i = 1; i <= n;i++)
  {
      w1 = u1[i]+_w2*v1[i];
      w2 = u2[i]+_w2*v2[i];
      x = a + i*h;

      printf("%lf,%lf,%lf,%lf,%lf\n",x,u1[i],v1[i],w1,w2);
      fprintf(arq,"%lf\t%lf\t%lf\n",x,w1,w2);
  }

  fclose(arq);
  return 0;
}
```

# Método das diferenças finitas

O método das diferenças finitas (MDF) é um método de resolução de equações diferenciais que se baseia na aproximação de derivadas por diferenças finitas. A fórmula de aproximação obtém-se da série de Taylor da função derivada. Atualmente, os MDFs são a abordagem dominante das soluções numéricas de equações diferenciais parciais.

O operador de diferenças finitas para derivada pode ser obtido a partir da série de Taylor para as seguintes funções:

![mdf1](https://wikimedia.org/api/rest_v1/media/math/render/svg/47dab2c68ecb0a962d5b45620c114b399e187a94)

