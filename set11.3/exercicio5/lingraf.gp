set terminal pngcairo

set key left
set autoscale
set xlabel 'X'
set ylabel 'Y'

f(x) = exp(-10*x)
#fit f(x) 'dados1.txt' via a

set output 'fig11.3.5a.png'
plot f(x) lc 'black' t'Curva exata', 'dados1.txt' pt 7 lc 'red' t'solução numerica h = 0.1'

set output 'fig11.3.5b.png'
plot f(x) lc 'black' t'Curva exata', 'dados2.txt' pt 7 lc 'red' t'solução numerica h = 0.05'

unset output
unset terminal
