set terminal pngcairo

set key left
set autoscale
set xlabel 'X'
set ylabel 'Y'

f(x) = exp(-10*x)
#fit f(x) 'dados1.txt' via a

set output 'fig11.1.5a.png'
plot f(x) lc 'black' t'Curva exata', 'dados3.txt' pt 7 lc 'red' t'solução numerica h = 0.1'

#set xlabel 'sen(Θ_i)'
#set ylabel 'sen(Θ_t)'

#fit f(x) 'dados2.txt' via a

set output 'fig11.1.5b.png'
plot f(x) lc 'black' t'Curva exata', 'dados4.txt' u 1:2 pt 7 lc 'red' t'solução numerica h = 0.05'

unset output
unset terminal
