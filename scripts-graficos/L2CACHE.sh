#!/usr/bin/gnuplot
reset
set term png size 1000,1000
set output 'L2CACHEGS.png'
set style line 1 lt rgb "purple" lw 3 pt 6
set style line 2 lt rgb "green" lw 3 pt 6
set xlabel "Tamanho"
set ylabel "data cache miss ratio"
set title "Cache miss L2 Gauss-Seidel"

plot "L2CACHEGS.dat" u 1:2 with linespoints ls 1 title "OTIMIZADO", \
"L2CACHEGSNO.Ini" u 1:2 with linespoints ls 2 title "NÃO OTIMIZADO"

reset
set term png size 1000,1000
set output 'L2CACHERES.png'
set style line 1 lt rgb "purple" lw 3 pt 6
set style line 2 lt rgb "green" lw 3 pt 6
set xlabel "Tamanho"
set ylabel "data cache miss ratio"
set title "Cache miss L2 Resíduo"

plot "L2CACHERES.dat" u 1:2 with linespoints ls 1 title "OTIMIZADO", \
"L2CACHERESNO.Ini" u 1:2 with linespoints ls 2 title "NÃO OTIMIZADO"
