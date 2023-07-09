#!/usr/bin/gnuplot
reset
set term png size 1000,1000
set output 'MemorydbGS.png'
set style line 1 lt rgb "purple" lw 3 pt 6
set style line 2 lt rgb "green" lw 3 pt 6
set xlabel "Tamanho"
set ylabel "Memory bandwidth [MBytes/s]"
set title "Banda de Memória Gauss-Seidel"

plot "MEMORYDBGS.dat" u 1:2 with linespoints ls 1 title "OTIMIZADO", \
"MEMORYDBGSNO.Ini" u 1:2 with linespoints ls 2 title "NÃO OTIMIZADO"

reset
set term png size 1000,1000
set output 'MemorydbRES.png'
set style line 1 lt rgb "purple" lw 3 pt 6
set style line 2 lt rgb "green" lw 3 pt 6
set xlabel "Tamanho"
set ylabel "Memory bandwidth [MBytes/s]"
set title "Banda de Memória Resíduo"

plot "MEMORYDBRES.dat" u 1:2 with linespoints ls 1 title "OTIMIZADO", \
"MEMORYDBRESNO.Ini" u 1:2 with linespoints ls 2 title "NÃO OTIMIZADO"
