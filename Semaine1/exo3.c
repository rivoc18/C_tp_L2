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
#include <math.h>

float min(float tab[], int taille)
{
	float min;
	int i;

	i = 0;
	min = tab[i];
	while (i < taille)
	{
		if (tab[i] < min)
			min = tab[i];
		i++;
	}
	return (min);
}

int indice_min(float tab[], int taille)
{
	int imin;
	int i;

	i = 0;
	imin = 0;
	while (i < taille)
	{
		if (tab[i] < tab[imin])
			imin = i;
		i++;
	}
	return (imin);

}

int main(int argc, const char *argv[])
{
	float tab[5] = {1.43433, 1.3236, 0.786857, 0.039908, 23.8};
	printf("%f\n", min(tab, 5));
	printf("%d\n", indice_min(tab, 5));
	return 0;
}
