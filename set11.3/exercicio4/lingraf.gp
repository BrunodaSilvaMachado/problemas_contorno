set terminal pngcairo

set key right bottom
set autoscale
set xlabel 'X'
set ylabel 'Y'

f(x) = 4.0*x**-1 -2.0*x**-2 + log(x) -3.0/2.0
#fit f(x) 'dados1.txt' via a

set output 'fig11.3.4c.png'
plot f(x) lc 'black' t'Curva exata', 'dados1.txt' pt 7 lc 'red' t'solução numerica h = 0.05'

unset output
unset terminal
