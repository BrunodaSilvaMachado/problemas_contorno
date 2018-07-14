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
Os problemas (PVI-1) e (PVI-2) possuem cada um uma unica solução. Sejam y1(x) a solução de (PVI-1)
e y2(x) a solução de (PVI-2).
Uma conta fácil mostra que


