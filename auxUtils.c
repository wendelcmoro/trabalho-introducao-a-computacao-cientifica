/**
 * \file
 * \brief Contém a implementação da função que printa o sistema linear e demais informações da execução do programa.
 */

#include "auxUtils.h"

void prnSistLinear (SistLinear_t *SL, FILE *arq, double tempo, unsigned int MAXIT, int err)
{
	if (err == 0){
		fprintf (arq, "###########\n");
		fprintf (arq, "# Tempo Método GS: %e\n", tempo);
		fprintf (arq, "#\n");
		fprintf (arq, "# Norma L2 do Resíduo\n");
		
		for (int i = 0; i < MAXIT; i++){
			fprintf (arq, "#i=%d: %e\n", i+1, SL->r[i]);
		}
		fprintf (arq, "###########\n");
		
		real_t x = SL->hx;
		real_t y = SL->hy;
		
		for (int j = 1; j < SL->ny -1; j++){
			if (j == 1)
				fprintf (arq, "%d	", SL->nx*SL->ny);
			fprintf (arq, "%e	", y);
			y += SL->hy;
		}
		fprintf (arq, "\n");
		for (int i = 1; i < SL->nx - 1; i++){
			fprintf (arq, "%e	", x);
			for (int j = 1; j < SL->ny -1; j++){
				fprintf (arq , "%e	", SL->u[i*SL->ny + j]);
			}
				x += SL->hx;
				fprintf (arq, "\n");
			}
			fprintf (arq, "\n");
	}
	else if (err == 1){
		fprintf (arq, "1 - Ocorreu uma divisão por zero!!!!\n");
	}
	else if (err == 2){
		fprintf (arq, "2 - Gerou valor infinito!!!!\n");
	}
	else if (err == 3){
		fprintf (arq, "3 - Gerou valor Not a Number!!!!\n");
	}
	else if (err == 4){
		fprintf (arq, "4 - Argumento '-nx' não encontrado!!!!\n");
	}
	else if (err == 5){
		fprintf (arq, "5 - Valor de '-nx' não encontrado!!!!\n");
	}
	else if (err == 6){
		fprintf (arq, "6 - Argumento '-ny' não encontrado!!!!\n");
	}
	else if (err == 7){
		fprintf (arq, "7 - Valor de '-ny' não encontrado!!!!\n");
	}
	else if (err == 8){
		fprintf (arq, "8 - Argumento '-i' não encontrado!!!!\n");
	}
	else if (err == 9){
		fprintf (arq, "9 - Valor de '-i' não encontrado!!!!\n");
	}
	else if (err == 10){
		fprintf (arq, "10 - Valor de '-nx' não pode ser menor ou igual zero!!!!\n");
	}
	else if (err == 11){
		fprintf (arq, "11 - Valor de '-ny' não pode ser menor ou igual zero!!!!\n");
	}
	else if (err == 12){
		fprintf (arq, "12 - Não foi possível alocar memória\n");
	}
	else if (err == 13){
		fprintf (arq, "13 - Número de iterações precisa ser maior que zero\n");
	}
	
}

