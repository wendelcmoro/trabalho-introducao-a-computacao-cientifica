/**
 * \name teste
 * \mainpage Documetação do programa pdeSolver
 * 
 * \section Equipe
 * Leonardo Ferreira Luciano - GRR20182576<br>
 * Wendel Caio Moro - GRR20182641
 * 
 * \section Objetivo
 * O programa tem por objetivo resolver a seguinte equação diferencial parcial:
 * \f[
 * k\bigg(\frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2}\bigg) +
 * \lambda\bigg(\frac{\partial u}{\partial x} + \frac{\partial u}{\partial y}\bigg) +
 * \eta u(x, y) = f(x, y), (x, y) \in \Omega
 * \f]
 * onde
 * \f[
 * k = -1, \lambda = 1, \eta = 4\pi^2
 * \f]
 * \f[
 * f(x, y) = 4\pi^2[sin(2\pi x)sinh(\pi x) + sin(2\pi(\pi - x))\sinh(\pi(\pi - y))].
 * \f]
 * Sendo o domínio
 * \f[
 * \Omega = [0, \pi] \times [0, \pi]
 * \f]
 * e os valores de suas derivadas nas bordas:
 * \f[
 * u(x, 0) = sin(2\pi(\pi - x))sinh(\pi^2)
 * \f]
 * \f[
 * u(x, \pi) = sin(2\pi x)sinh(\pi^2)
 * \f]
 * \f[
 * u(0, y) = u(\pi, y) = 0.
 * \f]<br>
 * O método utilizado será o das diferenças finitas e, para a resolução do sistema linear oriundo de tal método,
 * será utilizado o método de Gauss-Seidel.
 * 
 * \section Utilização
 * Pode-se executar o programa com os seguintes comandos:<br><br>
 * make<br>
 * ./pdeSolver -nx a -ny b -i c -o exemplo.dat
 * <br><br>onde a é número de pontos a serem calculados no eixo x, b é o número de pontos as serem calculados
 * no eixo y, c é o número de iterações que Gauss-Seidel deve realizar e example.dat é nome do arquivo de saída.<br><br>
 * 
 * O arquivo de saída conteḿ, nessa ordem, o tempo total de iteração de Gauss-Seidel, o resíduo a cada
 * uma dessas iterações e a matriz u formatada para ser plotada pelo gnuplot.
 * 
 * \section Plot
 * O gráfico no arquivo de saída (que aqui chamaremos de exemplo.dat) pode ser printado com os seguintes
 * comandos:<br><br>
 * gnuplot
 * set ticslevel 0<br>
 * splot 'exemplo.dat' nonuniform matrix with lines t ""  
 */

/**
 * \file
 * \brief Contém a função main que, ao ser executada, resolve a equação diferencial parcial e printa o resultado no arquivo de saída,
 * de acordo com os argumentos passados pelo usuário na chamada para a execução do programa.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistLinearUtils.h"
#include "gsUtils.h"
#include "auxUtils.h"
#include <likwid.h>

/**
 * Função main. Aloca o sistema linear do tipo SistLinear_t, inicializa seus valores, calcula o vetor solução u do sistema linear, ou seja,
 * calcula o valor para os pontos do grid desejados, bem como o tempo de execução de Gauss-Seidel e o resíduo a cada iteração e printa essas
 * informações, junto com a informação de status de execução do programa, no arquivo de saída indicado pelo usuário ou, caso o usuário
 * não tenha indicado nenhum arquivo, na saída padrão.<br><br>
 * Códigos de erros:<br><br>
 * 4  - Argumento "-nx" não foi especificado na entrada<br>
 * 5  - Valor de "-nx" não foi especificado na entrada<br>
 * 6  - Argumento "-ny" não foi especificado na entrada<br>
 * 7  - Valor de "-ny" não foi especificado na entrada<br>
 * 8  - Argumento "-i" não foi especificado na entrada<br>
 * 9  - Valor de "-i" não foi especificado na entrada<br>
 * 10 - Valor de "-nx" não pode ser menor ou igual a zero<br>
 * 11 - Valor de "-ny" não pode ser menor ou igual a zero<br>
 * 12 - Não foi possível alocar memória<br>
 * 13 - Valor de "-i" não pode ser menor ou igual a zero<br>
 * \param argc Parâmetro padrão da função main que representa o número de argumentos recebidos na chamada da função
 * \param argv Parâmetro padrão da função main que aponta para o inicio do vetor com todos os parâmetros recebidos na chamada da função
 */
int main(int argc, char **argv) {
	LIKWID_MARKER_INIT;

    // Le os parametros passados para o programa
	
    if (argv[1] != NULL){
		if (strcmp(argv[1],"-nx") == 0){
			
			if (argv[2] != NULL){
				int nx = atoi(argv[2]);
				
				if (nx > 0){
					if (argv[3] != NULL){
						if (strcmp(argv[3],"-ny") == 0){
							
							if (argv[4] != NULL){
								int ny = atoi(argv[4]);
								
								if (ny > 0){
									if (argv[5] != NULL){
										if (strcmp(argv[5],"-i") == 0){
											
											if (argv[6] != NULL){
												int MAXIT = atoi(argv[6]);
												if (MAXIT > 0){
													SistLinear_t *SL = constroeSistLinear(nx, ny, MAXIT);
													if (SL != NULL){
														double tempo;
														int erro = gaussSeidel(SL, MAXIT, &tempo);
														
														if (argv[7] == NULL){
															prnSistLinear(SL, stdout, tempo, MAXIT, erro);
														}
														else if (strcmp(argv[7], "-o") == 0){
															
															if (argv[8] != NULL){
																FILE *arquivo;
																arquivo = fopen(argv[8], "w+");
																prnSistLinear(SL, arquivo, tempo, MAXIT, erro);
																fclose(arquivo);
															}
															else
																prnSistLinear(SL, stdout, tempo, MAXIT, erro);
																
														}
														
														liberaSistLinear(SL);
													}
													else
														prnSistLinear(NULL, stderr, 0, 0, 12);
												}
												else
													prnSistLinear(NULL, stderr, 0, 0, 13);
											}
											else
												prnSistLinear(NULL, stderr, 0, 0, 9);
										}
										else
											prnSistLinear(NULL, stderr, 0, 0, 8);
									}
									else
										prnSistLinear(NULL, stderr, 0, 0, 8);
								}
								else
									prnSistLinear(NULL, stderr, 0, 0, 11);
							}
							else
								prnSistLinear(NULL, stderr, 0, 0, 7);
						}
						else
							prnSistLinear(NULL, stderr, 0, 0, 6);
					}
					else
						prnSistLinear(NULL, stderr, 0, 0, 6);
				}
				else
					prnSistLinear(NULL, stderr, 0, 0, 10);
			}
			else
				prnSistLinear(NULL, stderr, 0, 0, 5);
		}
		else
			prnSistLinear(NULL, stderr, 0, 0, 4);
	}
	else
		prnSistLinear(NULL, stderr, 0, 0, 4);

	LIKWID_MARKER_CLOSE;

    return 0;
}
