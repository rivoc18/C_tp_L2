#include "csvl.h"

int main (){

	char *str = "test chaine tzfyfkhfjfsgsg";
	char **tab;

	printf("\n------------ compte mot chaine: -----------\n");
	printf("%d\n",compte_mots_chaine(str));

	printf("\n------------ decompose_chaine: ------------\n");
	tab = decompose_chaine(str);
	affiche_tab_mots(decompose_chaine(str));

	printf("\n------------ compose_chaine: --------------\n");
	printf("%s", compose_chaine( decompose_chaine(str) ) );

	printf("\n\n------------ reduit_tab_mots: -------------\n");
	tab = reduit_tab_mots(tab);
	int i = 0;
	while (tab[i]){
		printf("%s\t->\t%p\n", tab[i], tab[i]);
		i++;
	}
	
	detruit_tab_mots(tab);
	
	return 0;
}
