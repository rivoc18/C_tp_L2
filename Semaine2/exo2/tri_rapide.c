#include "utilitaires_tableaux.h"
#include "tri_rapide.h"
#include <stdlib.h>
#include <stdio.h>

void triRapide(int tab[], int n) {
	int pivot = tab[0];
	int itab1=0;
	int itab2=0;
	
	if (n > 1) {
		int *tab1 = nouveau_tableau(n - 1);
		int *tab2 = nouveau_tableau(n - 1);
		int i;
		for (i = 1; i < n; i++){
			if (tab[i] <= pivot){
				tab1[itab1]=tab[i];
				itab1++;
			}else{
				tab2[itab2]=tab[i];
				itab2++;
			}
		}

		triRapide(tab1,itab1);
		triRapide(tab2,itab2);

		copier_tab(tab1,tab,itab1);
		tab[itab1]=pivot;
		copier_tab(tab2,tab+itab1+1,itab2);
		
		detruire_tableau(tab1);
		detruire_tableau(tab2);
	}
}

int partitionner(int tab[], int s, int n)
{
	int p = 0;
	int i;
	int save;

	p = s;
	for (i = s + 1; i < n; i++)
	{
		if (tab[i] <= tab[s])
		{
			p++;
			save = tab[p];
			tab[p] = tab[i];
			tab[i] = save;
			//echanger_elem_tab(tab, tab[p], tab[i]);
		}
	}
	save = tab[s];
	tab[s] = tab[p];
	tab[p] = save;
	//echanger_elem_tab(tab, tab[s], tab[p]);
    return p;
}

void triRapideAmeliore(int tab[], int s, int n)
{
	int p;

	if (n - s > 1)
	{
		p = partitionner(tab, s, n);
		triRapideAmeliore(tab, s, p);
		triRapideAmeliore(tab,p + 1, n);
	}
}
/*
int main(){
	int tab[TAILLE];
	init_tab_alea(tab, TAILLE);	
	//afficher_tab(tab, TAILLE);
	triRapideAmeliore(tab, 0, TAILLE);
	//afficher_tab(tab, TAILLE);
	if (tab_trie(tab, TAILLE))
		printf("Tableau trie\n");
	 else
		printf("Tableau non trie\n");
	return (0);
}
*/