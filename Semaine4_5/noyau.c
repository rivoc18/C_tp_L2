#include <stdlib.h>
#include "noyau.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TMP_STR_SIZE 128

noyau_t *creer_noyau(unsigned int dim)
{
	noyau_t *noyau;

	//on alloue la ram pour le noyau
	if((noyau = (noyau_t *)malloc(sizeof(noyau_t))) == NULL)
		return NULL;
	noyau->dim = dim;
	//on alloue de la ram pour coeffs
	if ((noyau->coeffs = (int *)malloc(sizeof(int) * (dim * dim))) == NULL)
		return NULL;
	return noyau;
}

void detruire_noyau(noyau_t *pn)
{
	if (pn == NULL) return ;
	free(pn->coeffs);
	free(pn);
}

noyau_t *charger_noyau(char *nom_fichier)
{
	FILE *f = fopen(nom_fichier, "r");
	if (f == NULL) return NULL;
	noyau_t *noyau;
	int dim;

	//on lis la dimension + creer un noyau avec + affecte la variable dim dedans
	fscanf(f, " %u ", &dim);
	noyau = creer_noyau(dim);
	noyau->dim = dim;

	//on parcours toutes les valeurs et on les ajoutes a coeffs
	int i;
	for (i = 0; i < dim*dim; i++){
		fscanf(f, " %d ", (noyau->coeffs) + i);
	}
	fclose(f);
	return noyau;
}
