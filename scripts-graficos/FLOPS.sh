#!/usr/bin/gnuplot
reset
set term png size 1000,1000
set output 'FLOPSDPGS.png'
set style line 1 lt rgb "purple" lw 3 pt 6
set style line 2 lt rgb "green" lw 3 pt 6
set style line 3 lt rgb "blue" lw 3 pt 6
set style line 4 lt rgb "red" lw 3 pt 6
set xlabel "Tamanho"
set ylabel "MFLOP/s"
set title "Operações aritméticas Gauss-Seidel"

plot "FLOPSDPGS.dat" u 1:2 with linespoints ls 1 title "FLOPS-DP OTIMIZADO", \
"FLOPSDPGSNO.Ini" u 1:2 with linespoints ls 2 title "FLOPS-DP NÃO OTIMIZADO", \
"FLOPSAVXGS.dat" u 1:2 with linespoints ls 3 title "FLOPS-AVX OTIMIZADO", \
"FLOPSAVXGSNO.Ini" u 1:2 with linespoints ls 4 title "FLOPS-AVX NÃO OTIMIZADO", \

reset
set term png size 1000,1000
set output 'FLOPSDPRES.png'
set style line 1 lt rgb "purple" lw 3 pt 6
set style line 2 lt rgb "green" lw 3 pt 6
set style line 3 lt rgb "blue" lw 3 pt 6
set style line 4 lt rgb "red" lw 3 pt 6
set xlabel "Tamanho"
set ylabel "MFLOP/s"
set title "Operações aritméticas Resíduo"

plot "FLOPSDPRES.dat" u 1:2 with linespoints ls 1 title "FLOPS-DP OTIMIZADO", \
"FLOPSDPRESNO.Ini" u 1:2 with linespoints ls 2 title "FLOPS-DP NÃO OTIMIZADO", \
"FLOPSAVXRES.dat" u 1:2 with linespoints ls 3 title "FLOPS-AVX OTIMIZADO", \
"FLOPSAVXGSNO.Ini" u 1:2 with linespoints ls 4 title "FLOPS-AVX NÃO OTIMIZADO", \
