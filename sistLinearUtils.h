/**
 * \file
 * \brief Contém a estrutura de dados e os protótipos das funções usados para alocar e iniciar um sistema linear no formato que poder ser resolvido
 * pelo programa.
 */

#ifndef __SIST_LINEAR_UTILS__
#define __SIST_LINEAR_UTILS__

#include <stdlib.h>
#include <math.h>

/**
 * Tipo decimal que será usado no program. Facilita a troca de precisão float e double.
 */
typedef double real_t;

/**
 * \struct
 * Tipo de sistema linear aceito pelo programa. Todas as bordas são consideredas.<br><br>
 */
typedef struct {
  unsigned int nx; /**< Número de pontos a serem calculados no eixo x mais 2, ou seja, contando as bordas. */
  unsigned int ny; /**< Número de pontos a serem calculados no eixo y mais 2, ou seja, contando as bordas. */
  unsigned int n;
  real_t hx; /**< Tamanho do passo no eixo x. */
  real_t hy; /**< Tamanho do passo no eixo y. */
  real_t A[5]; /**< Ponteiro para o vetor de 5 posições que representa a matriz A. */
  real_t *u; /**< Ponteiro para o vetor de 5 posições que representa a matriz A. */ 
  real_t *b; /**< Ponteiro para o vetor resultado tal que b = Au. */
  real_t *r; /**< Vetor com os resíduos a cada iteração de Gauss-Seidel. */
  
} SistLinear_t;

/** 
 * Aloca à memória necessária para a estrutura de dados SistLinear_t.<br>
 * O retorno da função é um ponteiro para uma estrutura de dados do tipo SistLinear_t ou para null, se não foi possível alocar a memória.
 * \param nx número de pontos a serem calculados no eixo x
 * \param ny número de pontos a serem calculados no eixo y
 * \param MAXIT número máximo de iterações que o método de Gauss-Seidel deverá realizar
 */
SistLinear_t * alocaSistLinear(unsigned int nx, unsigned int ny, unsigned int MAXIT);

/**
 * Aloca a memória e atribui os valores iniciais a estrutura de dados SistLinear_t. Atribui a A e b os seus valores e preenche u com zeros,
 * exceto nas posições que representam bordas, onde os valores de tais bordas são atribuídos.<br>
 * O retorno da função é um ponteiro para uma estrutura de dados do tipo SistLinear_t.
 * \param nx número de pontos a serem calculados no eixo x
 * \param ny número de pontos a serem calculados no eixo y
 * \param MAXIT número de iterações que Gauss-Seidel irá realizar
 */
SistLinear_t * constroeSistLinear(unsigned int nx , unsigned int ny, unsigned int MAXIT);

/** 
 * Libera a memória alocada para uma estrutura de dados do tipo SistLinear_t.<br>
 * A função não retorna valor algum.
 * \param SL Ponteiro para o sistema linear a ser desalocado
 */
void liberaSistLinear(SistLinear_t *SL);

/** 
 * Retorna o valor do coeficiente de u na posição i, j, sendo que i é o indice do eixo x e j, do eixo y.
 * \param hx tamanho do passo no eixo x
 * \param hy tamanho do passo no eixo y
 */
real_t uij(real_t hx, real_t hy);

/** 
 * Retorna o valor do coeficiente de u na posição i - 1, j, sendo que i é o indice do eixo x e j, do eixo y.
 * \param hx tamanho do passo no eixo x
 */
real_t uia(real_t hx);

/** 
 * Retorna o valor do coeficiente de u na posição i + 1, j, sendo que i é o indice do eixo x e j, do eixo y.
 * \param hx Tamanho do passo no eixo x
 */
real_t uis(real_t hx);

/** 
 * Retorna o valor do coeficiente u na posição i, j - 1, sendo que i é o indice do eixo x e j, do eixo y.
 * \param hx Tamanho do passo no eixo y
 */
real_t uja(real_t hy);

/** 
 * Retorna o valor do coeficiente de u na posição i, j + 1, sendo que i é o indice do eixo x e j, do eixo y.
 * \param hx Tamanho do passo no eixo y
 */
real_t ujs(real_t hy);

/** 
 * Retorna o valor da função f na posição i, j, sendo que i é o indice do eixo x e j, do eixo y.
 * \param x Ponto no eixo x do grid
 * \param y Ponto no eixo y do grid
 */
real_t fxy(real_t x, real_t y);

/** 
 * Retorna o valor da função u na posição i da borda y = 0. Sendo que i é o indice do eixo x.
 * \param hx Tamanho do passo no eixo x
 */
real_t ux0(real_t x);

/** 
 * Retorna o valor da função u na posição i da borda y = pi. Sendo que i é o indice do eixo x.
 * \param hx Tamanho do passo no eixo x
 */
real_t uxp(real_t x);

#endif
