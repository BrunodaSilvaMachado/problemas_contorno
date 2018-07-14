set terminal pngcairo

set key left
set autoscale
set xlabel 'X'
set ylabel 'Y'

f(x) = -(sin(x)+3*cos(x))/10.0
#fit f(x) 'dados1.txt' via a

set output 'fig11.3.1a.png'
plot f(x) lc 'black' t'Curva exata', 'dados1.txt' pt 7 lc 'red' t'solução numerica h = π/4'

#set xlabel 'sen(Θ_i)'
#set ylabel 'sen(Θ_t)'

#fit f(x) 'dados2.txt' via a

set output 'fig11.3.1b.png'
plot f(x) lc 'black' t'Curva exata', 'dados2.txt' u 1:2 pt 7 lc 'red' t'solução numerica h = π/8'

unset output
unset terminal
