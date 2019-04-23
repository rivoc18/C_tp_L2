#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "abr.h"

int main(int argc, char **argv)
{
	if(argc < 2 ){
		printf("structure : executable nbBoucle\n");	
		exit(1);
	}
	int i;
  	Lm_mot *l = lire_dico_Lmot("french_za");
	Nd_mot *a = Lm2abr(l);
	Nd_mot *mot;
	char *m = "bon";
	
	for (i = 0; i < atoi(argv[1]); i++)
		mot = chercher_Nd_mot(a, m);

	if(mot)
		printf("le mot %s est dans l'arbre\n", mot->mot);
	else
		printf("le mot %s n'est pas dans l'arbre\n", m);
		
 	return 0;
}
