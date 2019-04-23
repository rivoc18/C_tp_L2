#include "utilitaires_tableaux.h"

void triBulle(int tab[], int n)
{
	int i,j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n-1-i; j++){
			if(tab[j+1]<tab[j])
				echanger_elem_tab(tab, j, j+1);		
		}
	}
}

void triBulleAmeliore(int tab[], int n)
{
	int i,j;
	int check;
	
	for(i = 0; i < n; i++){
		check = 0;
		for(j = 0; j < n-1-i; j++){
			if(tab[j+1]<tab[j]){
				echanger_elem_tab(tab, j, j+1);
				check = 1;
			}
		}
		if(!check)
			break ;
	}

}

