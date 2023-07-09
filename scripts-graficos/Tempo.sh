#!/usr/bin/gnuplot
reset
set term png size 1000,1000
set output 'TempoGS.png'
set style line 1 lt rgb "purple" lw 3 pt 6
set style line 2 lt rgb "green" lw 3 pt 6
set logscale y 2
set xlabel "Tamanho"
set ylabel "Tempo em ms"
set title "Teste de Tempo Gauss-Seidel"

plot "TEMPOGS.dat" u 1:2 with linespoints ls 1 title "OTIMIZADO", \
"TEMPOGSNO.Ini" u 1:2 with linespoints ls 2 title "NÃO OTIMIZADO"

reset
set term png size 1000,1000
set output 'TempoRES.png'
set style line 1 lt rgb "purple" lw 3 pt 6
set style line 2 lt rgb "green" lw 3 pt 6
set logscale y 2
set xlabel "Tamanho"
set ylabel "Tempo em ms"
set title "Teste de Tempo Resíduo"

plot "TEMPORES.dat" u 1:2 with linespoints ls 1 title "OTIMIZADO", \
"TEMPORESNO.Ini" u 1:2 with linespoints ls 2 title "NÃO OTIMIZADO"
