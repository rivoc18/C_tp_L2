/*******************************************************************************
 *
 *    __  ______  __  _________
 *   / / / / __ \/  |/  / ____/
 *  / / / / /_/ / /|_/ / /
 * / /_/ / ____/ /  / / /___
 * \____/_/   /_/  /_/\____/
 * +	Version non demandée en TME - avec generation de tableau aléatoire et
 *		suppression d'obstacle aléatoirement jusqu'à trouver une solution
 *
 * +	Verification dans le cas ou on fait un detour, pour l'eviter.
 ******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define DIM 8

int labtest[DIM][DIM] = {{0,1,1,0,1,1,0,1}, {0,1,1,1,0,0,1,0}, {0,0,0,0,0,0,1,0}, {0,0,0,0,0,0,1,0}, {1,0,1,1,1,1,1,1}, {1,0,0,1,1,1,0,1}, {1,1,0,0,1,1,1,0}, {0,0,1,0,0,0,0,0}};

char palette[3] = {' ', '.', 'o'};

int isUseless(int lab[DIM][DIM], int i, int j)
{
	int cmpt = 0;
	if (j < DIM - 1 && lab[i][j + 1] == 2) cmpt++;
	if (j > 0 && lab[i][j - 1] == 2) cmpt++;
	if (i < DIM - 1 && lab[i + 1][j] == 2) cmpt++;
	if (i > 0 && lab[i - 1][j] == 2) cmpt++;

	if (cmpt > 1) return 1;
	return 0;
}

void afficher_lab(int lab[DIM][DIM], char palette[]){
	int i;
	int j;

	i = 0;
	printf("+");
	for (i = 0; i < DIM; i++)
		printf("--");
	printf("+\n");
	i = 0;
	for (i = 0; i < DIM; i++) {
		printf("|");
		for(j = 0; j < DIM; j++) {
			if (lab[i][j] == 0 || lab[i][j] == 3)
				printf("%c ", palette[0]);
			if (lab[i][j] == 1)
				printf("%c ", palette[1]);
			if (lab[i][j] == 2)
				printf("%c ", palette[2]);
		}
		printf("|\n");
	}
	i = 0;
	printf("+");
	for (i = 0; i < DIM; i++)
		printf("--");
	printf("+\n");
}

int chercher_chemin_rec(int lab[DIM][DIM], int lc, int cc){
	if (lc == DIM - 1 && cc == DIM - 1) {//on pose la condition d'arret: quand on est arrive a la derniere case
		lab[DIM - 1][DIM - 1] = 2;
		return (1);
	}
	if (isUseless(lab,lc,cc))
		return (0);

	lab[lc][cc] = 2; //on remplace la case sur laquelle on est (0) par un 2
	if ((cc < DIM - 1 && lab[lc][cc + 1] == 0 && chercher_chemin_rec(lab, lc, cc + 1))
		|| (lc < DIM - 1 && lab[lc + 1][cc] == 0 && chercher_chemin_rec(lab, lc + 1, cc))
		|| (cc > 0 && lab[lc][cc - 1] == 0 && chercher_chemin_rec(lab, lc, cc - 1))
		|| (lc > 0 && lab[lc - 1][cc] == 0 && chercher_chemin_rec(lab, lc - 1, cc)))
		return (1);
	lab[lc][cc] = 3; // si aucune solution n'est trouvee, alors on est bloque et on remplace le 2 par un 3.
	return (0);
}

int chercher_chemin(int lab[DIM][DIM]){
	return (chercher_chemin_rec(lab, 0, 0));
}

void init_random_tab(int lab[DIM][DIM]) {
	int i, j;
	for (i = 0; i < DIM; i++){
		for (j = 0; j < DIM; j++){
			lab[i][j] = rand() % 2;
		}
	}
	lab[0][0] = 0;   //on remplace la 1ere et derniere case par 0 (pour etre sur que la recursion bug pas)
	lab[DIM-1][DIM-1] = 0;
}

void clean_tab(int lab[DIM][DIM]) {
	int i, j;
	for (i = 0; i < DIM; i++){
		for (j = 0; j < DIM; j++){
			if (lab[i][j] == 3)
				lab[i][j] = 0;;
		}
	}
}

void random_remove_case_tab(int lab[DIM][DIM]) {
	int i, j;
	do {
		i = rand() % DIM;
		j = rand() % DIM;
	} while (lab[i][j] != 1);
	lab[i][j] = 0;
}

int main(){
	int lab[DIM][DIM];
	
	srand(time(NULL));
	init_random_tab(lab); // on genere un tableau aleatoirement
	afficher_lab(lab,palette);
	printf("\n");
	while (!chercher_chemin(lab)) //tant qu on a pas trouve de chemin
	{
		clean_tab(lab); //on vide le tableau de tout les 2 et 3 d'une precedente boucle
		random_remove_case_tab(lab); //on prend une case obstacle et on la remplace par du vide
	}
	afficher_lab(lab,palette);
	return (0);
}
