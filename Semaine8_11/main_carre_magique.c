
#include <stdio.h>
#include "carre_magique.h"
#include "liste.h"
#include "arbre_lexicographique_tab.h"

int main() {
	Lm_mot *dico = lire_dico_Lmot("french_za");
	carre_magique(dico, 3);
	detruire_Lmot(dico);
	return 0;
}
