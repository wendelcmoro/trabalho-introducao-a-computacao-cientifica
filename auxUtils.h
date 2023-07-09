/**
 * \file
 * \brief Contém o protótipo da função que printa o sistema linear e demais informações da execução do programa.
 */

#ifndef __AUX_UTILS__
#define __AUX_UTILS__

#include <stdio.h>
#include "sistLinearUtils.h"

/**
 * Printa o tempo total de execução e o resíduo para cada uma das iterações de Gauss-Seidal, o status em que o program se encerrou e
 * também o vetor u de SL de forma que possa ser plotado pelo gnuplot.<br>
 * Não retorna nenhum valor.<br><br>
 * Códigos de erros:<br><br>
 * 0 - Nenhum erro<br>
 * 1 - Divisão por 0<br>
 * 2 - Gerou Infinity<br>
 * 3 - Gerou Nan<br>
 * \param SL Ponteiro para o sistema linear
 * \param arq Ponteiro para o arquivo onde o sistema linear deve ser printado
 * \param tempo Tempo de execução de Gauss-Seidel
 * \param MAXIT Número de iterações que Gauss-Seidel irá realizar
 * \param err Status final de execução do programa
 */
void prnSistLinear(SistLinear_t *SL, FILE *arq, double tempo, unsigned int MAXIT, int err);

#endif
