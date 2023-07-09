/**
 * \file
 * \brief Contém a implementação das funções usadas para alocar e iniciar um sistema linear no formato que poder ser resolvido pelo programa.
 */

#include "sistLinearUtils.h"
#define N 4*M_PI*M_PI
#define LB 1
#define K -1

SistLinear_t * alocaSistLinear(unsigned int nx, unsigned int ny, unsigned int MAXIT) {
  SistLinear_t *SL = (SistLinear_t *) malloc(sizeof(SistLinear_t));
  if ( SL ) {
	unsigned int n = (nx + 2)* (ny + 2);
	SL->u = (real_t *) malloc(n * sizeof(real_t));
	SL->b = (real_t *) malloc(n * sizeof(real_t));
	
	SL->r = (real_t *) malloc(MAXIT * sizeof(real_t));

    if ( !(SL->u) || !(SL->b) ) {
      liberaSistLinear(SL);
	  return NULL;
	}
  }
  else
	return NULL;
  
  return (SL);
}

SistLinear_t * constroeSistLinear(unsigned int nx , unsigned int ny, unsigned int MAXIT) {
	SistLinear_t *SL = alocaSistLinear(nx, ny, MAXIT);

	SL->nx = nx + 2;
	SL->ny = ny + 2;
	SL->n = SL->nx * SL->ny;
	SL->hx = M_PI / (SL->nx - 1);
	SL->hy = M_PI / (SL->ny - 1);

	SL->A[0] = uis(SL->hx);
	SL->A[1] = uia(SL->hx);
	SL->A[2] = ujs(SL->hy);
	SL->A[3] = uja(SL->hy);
	SL->A[4] = uij(SL->hx, SL->hy);

	if (fabs(SL->A[4]) == 0)
		liberaSistLinear(SL);

	real_t x = 0;
	real_t y = 0;
	for (unsigned int i = 0; i < SL->nx; i++) {
		for (unsigned int j = 0; j < SL->ny; j++) {
			if (j == 0) {
				SL->u[i * SL->ny] = ux0(x);
				SL->b[i * SL->ny] = 0;
			} else if (j == SL->ny - 1) {
				SL->u[i * SL->ny + j] = uxp(x);
				SL->b[i * SL->ny + j] = 0;
			} else {
				SL->u[i * SL->ny + j] = 0;
				SL->b[i * SL->ny + j] = fxy(x, y);
			}
			y += SL->hy;
		}
		y = 0;
		x += SL->hx;
	}	
    
    return SL;
}

// Liberacao de memória
void liberaSistLinear (SistLinear_t *SL) {
  free(SL->u);
  free(SL->b);
  free(SL);
}

// Funções Derivadas Moduralizadas(Há um meio melhor de fazer?)
// Ui,j
real_t uij(real_t hx, real_t hy){
	return ( (-2*K)/pow(hx,2) + (-2*K)/pow(hy,2) + N  );
}

// Ui+1,j
real_t uia(real_t hx){
	return ( K/pow(hx,2) + LB/(2*hx) );
}

// Ui-1,j
real_t uis(real_t hx){
	return ( K/pow(hx,2) - LB/(2*hx) );
}

// Ui,j+1
real_t uja(real_t hy){
	return ( K/pow(hy,2) + LB/(2*hy) );
}
// Ui,j-1
real_t ujs(real_t hy){
	return ( K/pow(hy,2) - LB/(2*hy)  );
}

// F(x,y)
real_t fxy(real_t x, real_t y){
	return ( 4 * pow(M_PI, 2) * (sin(2 * M_PI * x) * sinh(M_PI * y) + sin(2 * M_PI * (M_PI - x)) * sinh(M_PI * (M_PI - y))) );
}

// *Funções de Bordas
// U(x,0)
real_t ux0(real_t x){
	return ( sin(2 * M_PI * (M_PI - x)) * sinh(pow(M_PI, 2)) );
}

// U(x,M_PI)
real_t uxp(real_t x){
	return ( sin(2 * M_PI * x) * sinh(pow(M_PI, 2)) );
}
