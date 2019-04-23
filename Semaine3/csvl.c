#include "csvl.h"

int compte_mots_chaine(char *chaine) {
	int i = 0;
	int res = 0;

	if (!isspace(chaine[0]))
		res = 1;
	while(chaine[i]){
		while(isspace(chaine[i])){
			i++;
			if(chaine[i] == '\0')
				return (res);
			if(!isspace(chaine[i]))
				res++;
		}
		i++;
	}
	if(!i)
		return 0;
	return res;
}

char **decompose_chaine(char *chaine)
{
	char **res;
	int i = 0;
	int j = 0;
	int k = 0;
	int z;

	//on malloc la premiere dimension avec le nb de mots
	if((res = (char **)malloc(sizeof(char *) * (compte_mots_chaine(chaine)+1))) == NULL)
		return NULL;

	//on parcours la chaine jusqu'au '\0'
	while (chaine[j])
	{
		//si le caractere n'est pas un espace
		if(!isspace(chaine[j])){
			k=j;
			//on va jusqu'au prochain espace et on recupere les indice de debut (j) et de fin (k) du mot
			while(chaine[k] && !isspace(chaine[k]))
				k++;;

			//ainsi on a la taille du mot et on malloc la taille
			if((res[i] = (char *)malloc(sizeof(char)*(k-j+1))) == NULL)
				return NULL;

			//puis on ajoute ce mot dans la case du tableau correspondante.
			for(z = j; z < k; z++)
				res[i][z - j] = chaine[z];
			res[i][z - j] = '\0';

			i++;
			j = k-1; //ne pas oublier le j = k pour passer au mot suivant !!!!!!!
		}
		j++;
	}
	res[i] = NULL;
	return res;
}

char *compose_chaine(char **ptab_mots)
{
	char *res;
	int nbMots = compte_mots(ptab_mots);
	int nbLettres = nbMots - 1; //les n-1 espaces qui separeront les mots
	int i = 0, j, x;

	while (ptab_mots[i])//on parcours toutes les chaines du tableau pour avoir le nbr de caractere TOTAL
	{
		j = 0;
		while(ptab_mots[i][j])
			j++;
		nbLettres += j;
		i++;
	}
	//on malloc le tableau avec le nb total de lettres + 1 (\0);
	if ((res = (char *)malloc(sizeof(char) * (nbLettres + 1)) ) == NULL)
		return NULL;
	i = 0;
	x = 0;
	//on parcours les chaines
	while (ptab_mots[i]){
		j = 0;
		//pour chaque chaine, on parcours les caracteres et on les ajoutes à res
		while (ptab_mots[i][j]){
			res[x] = ptab_mots[i][j];
			x++;
			j++;
		}
		res[x++] = ' ';
		i++;
	}
	res[nbLettres] = '\0';
	return (res);
}

char **detruit_tab_mots(char **ptab_mots)
{
	int i=0;
	int j;
	int check;
	while(ptab_mots[i]){
		check = 0;
		for(j = 0; j < i; j++){
			if(ptab_mots[i] == ptab_mots[j])
			{
				check = 1;
				break ;
			}
		}
		if(!check)
			free(ptab_mots[i]);
		i++;
	}
	free(ptab_mots);
	return NULL;
}

int compte_mots(char **ptab_mots)
{
	int i=0;
	while(ptab_mots[i])
		i++;
	return i;
}

void affiche_tab_mots(char **ptab_mots)
{
	int i = 0;
	while(ptab_mots[i]){
		printf("%s\n",ptab_mots[i++]);
	}
}

char **reduit_tab_mots(char **ptab_mots)
{
	int i = 0;
	int j;
	while (ptab_mots[i])
	{
		for (j = 0; j < i; j++)
		{
			if (strcmp(ptab_mots[i], ptab_mots[j]) == 0){
				free(ptab_mots[i]);
				ptab_mots[i] = ptab_mots[j];
				break ;
			}
		}
		i++;
	}
	return ptab_mots;
}
