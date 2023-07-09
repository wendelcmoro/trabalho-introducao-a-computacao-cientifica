/**
 * \file
 * \brief Contém os protótipos das funções necessárias para a resolução de sistemas lineares usando Gauss-Seidel
 */

#ifndef __GS_UTILS__
#define __GS_UTILS__

#include <stdio.h>
#include <math.h>
#include "sistLinearUtils.h"
#include "timeUtils.h"

//likwid
#ifdef LIKWID_PERFMON
#include <likwid.h>
#else
#define LIKWID_MARKER_INIT
#define LIKWID_MARKER_THREADINIT
#define LIKWID_MARKER_SWITCH
#define LIKWID_MARKER_REGISTER(regionTag)
#define LIKWID_MARKER_START(regionTag)
#define LIKWID_MARKER_STOP(regionTag)
#define LIKWID_MARKER_CLOSE
#define LIKWID_MARKER_GET(regionTag, nevents, events, time, count)
#endif

/** 
 * Calcula os valores dos pontos internos da malha apliando Gauss-Seidel ao sistema linear que oriundo das equações diferenciais parciais
 * um número defindo de vezes, definindo o residuo para cada uma dessas iterações. Também é calculado o tempo total de todas as
 * iterações de Gauss-Seidel. É retornado status da funçãoe há retornos nos parâmetros SL e tempo.<br><br>
 * Códigos de erros:<br><br>
 * 0 - Nenhum erro<br>
 * 1 - Divisão por 0<br>
 * 2 - Gerou Infinity<br>
 * 3 - Gerou Nan<br>
 * \param SL Ponteiro para o sistema linear a ser resolvido e onde serão retornado o valor de u e do r
 * \param MAXIT número de iterações que Gauss-Seidel irá realizar
 * \param tempo Ponteiro onde será retornado o tempo total de execução de Gauss-Seidel
 */
int gaussSeidel(SistLinear_t *SL, unsigned int MAXIT, double *tempo);

/** 
 * Calcula norma L2 do resíduo de uma solução encontrada calculada para um sistema linear.
 * \param SL Ponteiro para o sistema linear a ser resolvido e onde serão retornado o valor de u e do r
 */
real_t normaL2Residuo(SistLinear_t *SL);

#endif
