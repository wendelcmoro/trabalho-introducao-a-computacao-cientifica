#!/bin/bash

make clean;
make;
testes=(32 50 64 100 128 200 256 300 400 512 1000 1024 2000 2048 3000 4000 4096 5000 10000);

echo '#tam TEMPO' > TEMPOGS.dat;
echo '#tam TEMPO' > TEMPORES.dat;
echo '#tam L2CACHE miss ratio' > L2CACHEGS.dat;
echo '#tam L2CACHE miss ratio' > L2CACHERES.dat;
echo '#tam FLOPS_DP' > FLOPSDPGS.dat;
echo '#tam FLOPS_DP' > FLOPSDPRES.dat;
echo '#tam FLOPS_AVX' > FLOPSAVXGS.dat;
echo '#tam FLOPS_AVX' > FLOPSAVXRES.dat;
echo '#tam Memory Bandwidth' > MEMORYDBGS.dat;
echo '#tam Memory Bandwidth' > MEMORYDBRES.dat;
echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor;
sleep 5s;
tempo1="a";
tempo2="a";

# TEMPO DE EXECUÇÃO + L2CACHE MISS RATIO
for i in ${testes[@]}
do
    echo "Executando teste de tamanho" $i "para Tempo e L2CACHE MISS"
    likwid-perfctr -C 3 -g L2CACHE -m ./pdeSolver -nx $i -ny $i -i 10 -o test.dat > Likwid.dat;

    # TEMPO DE EXECUÇÃO GS
    echo -n $i ' ' >> TEMPOGS.dat;
    tempo1=$(awk '/Runtime/{++n; if (n == 1) {print $6}}' Likwid.dat);
	
	# TEMPO DE EXECUÇÃO RES
    echo -n $i ' ' >> TEMPORES.dat;
	tempo2=$(awk '/Runtime/{++n; if (n == 4) {print $6}}' Likwid.dat);
	tempo1=$(awk '{print $1-$2}' <<<"${tempo1} ${tempo2}");
	tempo1=$(awk '{print $1*100}' <<<"${tempo1}");
	tempo2=$(awk '{print $1*100}' <<<"${tempo2}");
	echo $tempo1 >> TEMPOGS.dat;
	echo $tempo2 >> TEMPORES.dat; 
    
    # L2CACHE MISS RATIO GS
    echo -n $i ' ' >> L2CACHEGS.dat;
    awk '/ratio/{++n; if (n == 1) {print $6}}' Likwid.dat >> L2CACHEGS.dat;
    
    # L2CACHE MISS RATIO RES
    echo -n $i ' ' >> L2CACHERES.dat;
    awk '/ratio/{++n; if (n == 2) {print $6}}' Likwid.dat >> L2CACHERES.dat;
done

# Memory Bandwidth
for i in ${testes[@]}
do
    echo "Executando teste de tamanho" $i "para L3 BANDWIDTH"
    likwid-perfctr -C 3 -g L3 -m ./pdeSolver -nx $i -ny $i -i 10 -o test.dat > Likwid.dat;

    # Memory Bandwidth GS
    echo -n $i ' ' >> MEMORYDBGS.dat;
    awk '/L3 bandwidth/{++n; if (n == 1) {print $6}}' Likwid.dat >> MEMORYDBGS.dat;
    
    # Memory Bandwidth RES
    echo -n $i ' ' >> MEMORYDBRES.dat;
    awk '/L3 bandwidth/{++n; if (n == 2) {print $6}}' Likwid.dat >> MEMORYDBRES.dat;
done

# FLOPS_DP
for i in ${testes[@]}
do
    echo "Executando teste de tamanho" $i "para FLOPS_DP e FLOPS_AVX"
    likwid-perfctr -C 3 -g FLOPS_DP -m ./pdeSolver -nx $i -ny $i -i 10 -o test.dat > Likwid.dat;

    # FLOPS_DP GS
    echo -n $i ' ' >> FLOPSDPGS.dat;
    awk '/DP MFLOP/{++n; if (n == 1) {print $5}}' Likwid.dat >> FLOPSDPGS.dat;
    
    # FLOPS_DP RES
    echo -n $i ' ' >> FLOPSDPRES.dat;
    awk '/DP MFLOP/{++n; if (n == 3) {print $5}}' Likwid.dat >> FLOPSDPRES.dat;

    # FLOPS_AVX GS
    echo -n $i ' ' >> FLOPSAVXGS.dat;
    awk '/AVX DP MFLOP/{++n; if (n == 1) {print $6}}' Likwid.dat >> FLOPSAVXGS.dat;
    
    # FLOPS_AVX RES
    echo -n $i ' ' >> FLOPSAVXRES.dat;
    awk '/AVX DP MFLOP/{++n; if (n == 2) {print $6}}' Likwid.dat >> FLOPSAVXRES.dat;
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor;

mv TEMPOGS.dat scripts-graficos/;
mv TEMPORES.dat scripts-graficos/;
mv L2CACHEGS.dat scripts-graficos/;
mv L2CACHERES.dat scripts-graficos/;
mv FLOPSDPGS.dat scripts-graficos/;
mv FLOPSDPRES.dat scripts-graficos/;
mv FLOPSAVXGS.dat scripts-graficos/;
mv FLOPSAVXRES.dat scripts-graficos/;
mv MEMORYDBGS.dat scripts-graficos/;
mv MEMORYDBRES.dat scripts-graficos/;
