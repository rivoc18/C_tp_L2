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
#include <stdlib.h>
#include <time.h>

#define MAX 10

void init(int tab[], int taille)
{
	int i;

	srand(time(NULL)); //A METTRE DANS LE MAIN NORMALEMENT
	i = 0;
	while (i < taille)
	{
		tab[i] = rand()%(MAX);
		i++;
	}
}

void somme(int tab1[], int tab2[], int tab3[], int taille)
{
	int i;

	i = 0;
	while (i < taille)
	{
		tab3[i] = tab1[i] + tab2[i];
		i++;
	}
}
