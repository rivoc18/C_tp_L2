#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "arbre_lexicographique_tab.h"
#include "commun.h"
#include "mot_le_plus_long.h"
#include "liste.h"

int main() {
	char *lettres;
	lettres = (char *)malloc(27);

	write(1, "lettres à rechercher ? : ", 25);
	scanf("%s", lettres);

	int longueur;
	write(1, "longueur des mots à rechercher ? (-1 = le plus grand) : ", 56);
	scanf("%d", &longueur);

	PNoeudTab dico=lire_dico("french_za");

	//le mot le plus long
	if(longueur == -1){
		char *res = "";
		res = (char*)malloc(100);
		le_mot_le_plus_long(lettres, dico, res);
		printf("\nres : %s", res);
	}

	//mots de longueur donnée
	else{
		Lm_mot *l2 = mots_de_longueur_donnee(lettres, dico, longueur);
		afficher_Lmot(l2);
	}
	return 0;
}
