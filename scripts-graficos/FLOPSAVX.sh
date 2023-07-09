#!/usr/bin/gnuplot

set term png size 1000,1000
set output 'FLOPSAVX.png'
set style line 1 lt rgb "purple" lw 3 pt 6
set style line 2 lt rgb "green" lw 3 pt 6
set xlabel "Tamanho"
set ylabel "FLOPS_AVX /S"
set title "FLOPS_AVX"

plot "FLOPSAVX.dat" u 1:2 with linespoints ls 1 title "OTIMIZADO", \
"FLOPSAVXNO.Ini" u 1:2 with linespoints ls 2 title "NÃO OTIMIZADO"
