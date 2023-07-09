/**
 * \file
 * \brief Contém a implementação das funções necessárias para a resolução de sistemas lineares usando Gauss-Seidel
 */

#include "gsUtils.h"
#include <likwid.h>

int gaussSeidel(SistLinear_t *SL, unsigned int MAXIT, double *tempo) {
	LIKWID_MARKER_START("gauss-seidel");

	double tempo0;
	double tempo1;

	unsigned int maiorMult;
	for (unsigned int counter = 0; counter < MAXIT; counter++) {
		tempo0 = timestamp();

		for (unsigned int i = 1; i < SL->nx - 1; i++) {
			maiorMult = SL->ny - ((SL->ny - 2) % 8);
			for (unsigned int j = 1; j < maiorMult - 1; j += 8) {
				SL->u[i * SL->ny + j] = ( 
											SL->b[i * SL->ny + j] - SL->u[(i - 1) * SL->ny + j] * SL->A[0]
																  - SL->u[(i + 1) * SL->ny + j] * SL->A[1]
																  - SL->u[i * SL->ny + (j - 1)] * SL->A[2]
																  - SL->u[i * SL->ny + (j + 1)] * SL->A[3]
										) / SL->A[4];
				
				if (isinf(SL->u[i * SL->ny + j]))
					return 2;
					
				if (isnan(SL->u[i * SL->ny + j]))
					return 3;

				SL->u[i * SL->ny + j + 1] = ( 
											SL->b[i * SL->ny + j + 1] - SL->u[(i - 1) * SL->ny + j + 1] * SL->A[0]
																      - SL->u[(i + 1) * SL->ny + j + 1] * SL->A[1]
																      - SL->u[i * SL->ny + (j)] * SL->A[2]
																      - SL->u[i * SL->ny + (j + 2)] * SL->A[3]
										) / SL->A[4];
				
				if (isinf(SL->u[i * SL->ny + j + 1]))
					return 2;
					
				if (isnan(SL->u[i * SL->ny + j + 1]))
					return 3;

				SL->u[i * SL->ny + j + 2] = ( 
											SL->b[i * SL->ny + j + 2] - SL->u[(i - 1) * SL->ny + j + 2] * SL->A[0]
																      - SL->u[(i + 1) * SL->ny + j + 2] * SL->A[1]
																      - SL->u[i * SL->ny + (j + 1)] * SL->A[2]
																      - SL->u[i * SL->ny + (j + 3)] * SL->A[3]
										) / SL->A[4];
				
				if (isinf(SL->u[i * SL->ny + j + 2]))
					return 2;
					
				if (isnan(SL->u[i * SL->ny + j + 2]))
					return 3;

				SL->u[i * SL->ny + j + 3] = ( 
											SL->b[i * SL->ny + j + 3] - SL->u[(i - 1) * SL->ny + j + 3] * SL->A[0]
																      - SL->u[(i + 1) * SL->ny + j + 3] * SL->A[1]
																      - SL->u[i * SL->ny + (j + 2)] * SL->A[2]
																      - SL->u[i * SL->ny + (j + 4)] * SL->A[3]
										) / SL->A[4];
				
				if (isinf(SL->u[i * SL->ny + j + 3]))
					return 2;
					
				if (isnan(SL->u[i * SL->ny + j + 3]))
					return 3;

				SL->u[i * SL->ny + j + 4] = ( 
											SL->b[i * SL->ny + j + 4] - SL->u[(i - 1) * SL->ny + j + 4] * SL->A[0]
																      - SL->u[(i + 1) * SL->ny + j + 4] * SL->A[1]
																      - SL->u[i * SL->ny + (j + 3)] * SL->A[2]
																      - SL->u[i * SL->ny + (j + 5)] * SL->A[3]
										) / SL->A[4];
				
				if (isinf(SL->u[i * SL->ny + j + 4]))
					return 2;
					
				if (isnan(SL->u[i * SL->ny + j + 4]))
					return 3;
				
				SL->u[i * SL->ny + j + 5] = ( 
											SL->b[i * SL->ny + j + 5] - SL->u[(i - 1) * SL->ny + j + 5] * SL->A[0]
																      - SL->u[(i + 1) * SL->ny + j + 5] * SL->A[1]
																      - SL->u[i * SL->ny + (j + 4)] * SL->A[2]
																      - SL->u[i * SL->ny + (j + 6)] * SL->A[3]
										) / SL->A[4];
				
				if (isinf(SL->u[i * SL->ny + j + 5]))
					return 2;
					
				if (isnan(SL->u[i * SL->ny + j + 5]))
					return 3;

				SL->u[i * SL->ny + j + 6] = ( 
											SL->b[i * SL->ny + j + 6] - SL->u[(i - 1) * SL->ny + j + 6] * SL->A[0]
																      - SL->u[(i + 1) * SL->ny + j + 6] * SL->A[1]
																      - SL->u[i * SL->ny + (j + 5)] * SL->A[2]
																      - SL->u[i * SL->ny + (j + 7)] * SL->A[3]
										) / SL->A[4];
				
				if (isinf(SL->u[i * SL->ny + j + 6]))
					return 2;
					
				if (isnan(SL->u[i * SL->ny + j + 6]))
					return 3;

				SL->u[i * SL->ny + j + 7] = ( 
											SL->b[i * SL->ny + j + 7] - SL->u[(i - 1) * SL->ny + j + 7] * SL->A[0]
																      - SL->u[(i + 1) * SL->ny + j + 7] * SL->A[1]
																      - SL->u[i * SL->ny + (j + 6)] * SL->A[2]
																      - SL->u[i * SL->ny + (j + 8)] * SL->A[3]
										) / SL->A[4];
				
				if (isinf(SL->u[i * SL->ny + j + 7]))
					return 2;
					
				if (isnan(SL->u[i * SL->ny + j + 7]))
					return 3;
			}

			for (unsigned int j = maiorMult - 1; j < SL->nx - 1; j++) {
				SL->u[i * SL->ny + j] = ( 
											SL->b[i * SL->ny + j] - SL->u[(i - 1) * SL->ny + j] * SL->A[0]
																  - SL->u[(i + 1) * SL->ny + j] * SL->A[1]
																  - SL->u[i * SL->ny + (j - 1)] * SL->A[2]
																  - SL->u[i * SL->ny + (j + 1)] * SL->A[3]
										) / SL->A[4];
				
				if (isinf(SL->u[i * SL->ny + j]))
					return 2;
					
				if (isnan(SL->u[i * SL->ny + j]))
					return 3;
			}

		}

		SL->r[counter] = normaL2Residuo(SL);

		tempo1 = timestamp();
		*tempo += tempo1 - tempo0;
	}


	*tempo /= MAXIT;

	LIKWID_MARKER_STOP("gauss-seidel");	
	return 0;
}

real_t normaL2Residuo(SistLinear_t *SL) {
	LIKWID_MARKER_START("residuo");

	real_t raux;
	real_t r = 0.0;
	unsigned int maiorMult;

	for (unsigned int i = 2; i < SL->nx - 1; i++) {
		maiorMult = SL->ny - ((SL->ny - 2) % 8);
		for (unsigned int j = 1; j < maiorMult - 1; j += 8) {
			// Calcula residuo para linha anterior
			raux = SL->b[i * SL->ny + j] - SL->u[i * SL->ny + j] * SL->A[4]
												- SL->u[(i - 1) * SL->ny + j] * SL->A[0]
												- SL->u[(i + 1) * SL->ny + j] * SL->A[1]
												- SL->u[i * SL->ny + (j - 1)] * SL->A[2]
												- SL->u[i * SL->ny + (j + 1)] * SL->A[3];
			r += raux * raux;

			raux = SL->b[i * SL->ny + j + 1] - SL->u[i * SL->ny + j + 1] * SL->A[4]
													- SL->u[(i - 1) * SL->ny + j + 1] * SL->A[0]
													- SL->u[(i + 1) * SL->ny + j + 1] * SL->A[1]
													- SL->u[i * SL->ny + (j)] * SL->A[2]
													- SL->u[i * SL->ny + (j + 2)] * SL->A[3];
			r += raux * raux;

			raux = SL->b[i * SL->ny + j + 2] - SL->u[i * SL->ny + j + 2] * SL->A[4]
													- SL->u[(i - 1) * SL->ny + j + 2] * SL->A[0]
													- SL->u[(i + 1) * SL->ny + j + 2] * SL->A[1]
													- SL->u[i * SL->ny + (j + 1)] * SL->A[2]
													- SL->u[i * SL->ny + (j + 3)] * SL->A[3];
			r += raux * raux;

			raux = SL->b[i * SL->ny + j + 3] - SL->u[i * SL->ny + j + 3] * SL->A[4]
													- SL->u[(i - 1) * SL->ny + j + 3] * SL->A[0]
													- SL->u[(i + 1) * SL->ny + j + 3] * SL->A[1]
													- SL->u[i * SL->ny + (j + 2)] * SL->A[2]
													- SL->u[i * SL->ny + (j + 4)] * SL->A[3];
			r += raux * raux;

			raux = SL->b[i * SL->ny + j + 4] - SL->u[i * SL->ny + j + 4] * SL->A[4]
													- SL->u[(i - 1) * SL->ny + j + 4] * SL->A[0]
													- SL->u[(i + 1) * SL->ny + j + 4] * SL->A[1]
													- SL->u[i * SL->ny + (j + 3)] * SL->A[2]
													- SL->u[i * SL->ny + (j + 5)] * SL->A[3];
			r += raux * raux;
			
			raux = SL->b[i * SL->ny + j + 5] - SL->u[i * SL->ny + j + 5] * SL->A[4]
													- SL->u[(i - 1) * SL->ny + j + 5] * SL->A[0]
													- SL->u[(i + 1) * SL->ny + j + 5] * SL->A[1]
													- SL->u[i * SL->ny + (j + 4)] * SL->A[2]
													- SL->u[i * SL->ny + (j + 6)] * SL->A[3];
			r += raux * raux;
			
			raux = SL->b[i * SL->ny + j + 6] - SL->u[i * SL->ny + j + 6] * SL->A[4]
													- SL->u[(i - 1) * SL->ny + j + 6] * SL->A[0]
													- SL->u[(i + 1) * SL->ny + j + 6] * SL->A[1]
													- SL->u[i * SL->ny + (j + 5)] * SL->A[2]
													- SL->u[i * SL->ny + (j + 7)] * SL->A[3];
			r += raux * raux;
			
			raux = SL->b[i * SL->ny + j + 7] - SL->u[i * SL->ny + j + 7] * SL->A[4]
													- SL->u[(i - 1) * SL->ny + j + 7] * SL->A[0]
													- SL->u[(i + 1) * SL->ny + j + 7] * SL->A[1]
													- SL->u[i * SL->ny + (j + 6)] * SL->A[2]
													- SL->u[i * SL->ny + (j + 8)] * SL->A[3];
			r += raux * raux;
		}

		for (unsigned int j = maiorMult - 1; j < SL->nx - 1; j++) {
			// Calcula residuo para linha anterior
			raux = SL->b[i * SL->ny + j] - SL->u[i * SL->ny + j] * SL->A[4]
												- SL->u[(i - 1) * SL->ny + j] * SL->A[0]
												- SL->u[(i + 1) * SL->ny + j] * SL->A[1]
												- SL->u[i * SL->ny + (j - 1)] * SL->A[2]
												- SL->u[i * SL->ny + (j + 1)] * SL->A[3];
			r += raux * raux;
		}
	}

	LIKWID_MARKER_STOP("residuo");
	return sqrt(r);
}



