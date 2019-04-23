#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

int main(int argc, char **argv)
{
	if(argc < 2 ){
		printf("structure : executable nbBoucle\n");
		exit(1);
	}
	
	Lm_mot *mot;	
	Lm_mot *l = lire_dico_Lmot("french_za");
	char *m = "zonzon";
	int i;
	
	for (i = 0; i < atoi(argv[1]); i++)
		mot = chercher_Lm_mot(l, m);
	
	if(mot)
		printf("le mot %s est dans le dictionnaire\n", mot->mot);
	else
		printf("le mot %s n'est pas dans le dictionnaire\n", m);
		
  	return 0;
}
