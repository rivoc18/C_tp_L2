#include "utilitaires_tableaux.h"
#include "tri_bulle.h"

#define TAILLE 100

int main(){
	srand(time(NULL));
	int tab[TAILLE];
	init_tab_alea(tab,TAILLE);
	//afficher_tab(tab,TAILLE);
	triBulleAmeliore(tab,TAILLE);
	//afficher_tab(tab,TAILLE);
	return 0;
}
