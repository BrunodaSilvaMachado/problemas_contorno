set terminal pngcairo

set key left
set autoscale
set xlabel 'X'
set ylabel 'Y'

f(x) = 110*2/x * ((4.0 - x)/2.0)

set output 'fig11.1.7.png'
plot f(x) lc 'black' t'Curva exata', 'dados6.txt' pt 7 lc 'red' t'solução numerica n = 3'

unset output
unset terminal
