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

int		factorielle_ite(int nb)
{
	int res;

	res = 1;
	while (nb > 1)
	{
		res *= nb;
		nb--;
	}
	return (res);
}

int		factorielle_rec(int nb)
{
	if (nb == 1)
		return (1);
	return (nb * factorielle_rec(nb - 1));
}

int		main(int argc, const char *argv[])
{
	printf("iterative: %d\n", factorielle_ite(atoi(argv[1])));
	printf("recursive: %d", factorielle_rec(atoi(argv[1])));
	return 0;
}
