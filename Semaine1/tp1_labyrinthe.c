/*******************************************************************************
 *
 *    __  ______  __  _________
 *   / / / / __ \/  |/  / ____/
 *  / / / / /_/ / /|_/ / /
 * / /_/ / ____/ /  / / /___
 * \____/_/   /_/  /_/\____/
 *
 ******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define DIM 8

//int lab[DIM][DIM] = {{0,0,1,0,0,0,1,1}, {1,0,0,1,1,0,1,0}, {1,0,1,1,1,0,0,0}, {1,0,0,1,0,0,1,1}, {1,1,0,0,0,1,1,1}, {1,1,1,0,1,0,0,0}, {0,0,1,0,0,1,0,0}, {0,0,1,0,0,0,0,0}};
//int lab[DIM][DIM] = {{0,0,1,0,0,0,1,1}, {1,0,0,1,1,0,1,0}, {1,0,1,1,1,0,0,0}, {1,0,0,1,0,0,1,1}, {1,1,0,0,0,1,1,1}, {1,1,1,0,1,0,0,0}, {0,0,1,0,0,1,0,0}, {0,0,1,0,0,1,0,0}};
int lab[DIM][DIM] = {{0,0,1,0,0,0,1,1}, {1,0,0,0,1,0,1,0}, {1,0,1,1,1,0,0,0}, {1,0,0,1,0,0,1,1}, {1,1,0,0,0,1,1,1}, {1,1,1,0,1,0,0,0}, {0,0,1,0,0,0,1,0}, {0,0,1,0,0,0,1,0}};
//int lab[DIM][DIM] = {{0,1,0,0,0,1,1,1}, {0,0,0,1,0,1,0,1}, {1,1,1,1,0,1,1,1}, {1,1,1,1,0,1,1,1}, {0,0,0,0,0,0,1,1}, {0,1,1,1,1,1,1,1}, {0,0,0,0,0,0,0,0}, {1,1,1,1,0,0,1,0}};

char palette[3] = {' ', '.', 'o'};

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
	lab[lc][cc] = 2; //on remplace la case sur laquelle on est (0) par un 2 
	if (cc < DIM - 1 && lab[lc][cc + 1] == 0 && chercher_chemin_rec(lab, lc, cc + 1)) return (1); //aller a droite
	else if (lc < DIM - 1 && lab[lc + 1][cc] == 0 && chercher_chemin_rec(lab, lc + 1, cc)) return (1); //aller en bas
	else if (cc > 0 && lab[lc][cc - 1] == 0 && chercher_chemin_rec(lab, lc, cc - 1)) return (1); //aller a gauche
	else if (lc > 0 && lab[lc - 1][cc] == 0 && chercher_chemin_rec(lab, lc - 1, cc)) return (1); //aller en haut
	lab[lc][cc] = 3; // si aucune solution n'est trouvee, alors on est bloque et on remplace le 2 par un 3.
	return (0);
}

int chercher_chemin(int lab[DIM][DIM]){
	return (chercher_chemin_rec(lab, 0, 0));
}

int main(){
	if (chercher_chemin(lab))
		afficher_lab(lab,palette);
	else
		printf("Unsolved path");
	return (0);
}
