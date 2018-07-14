set terminal pngcairo

set key left
set autoscale
set xlabel 'X'
set ylabel 'Y'

f(x) = 0.2757205647717833*sinh(2*x) + x
#fit f(x) 'dados1.txt' via a

set output 'fig11.1.1a.png'
plot f(x) lc 'black' t'Curva exata', 'dados1.txt' pt 7 lc 'red' t'solução numerica h = 0.5'

#set xlabel 'sen(Θ_i)'
#set ylabel 'sen(Θ_t)'

#fit f(x) 'dados2.txt' via a

set output 'fig11.1.1b.png'
plot f(x) lc 'black' t'Curva exata', 'dados2.txt' u 1:2 pt 7 lc 'red' t'solução numerica h = 0.25'

unset output
unset terminal
