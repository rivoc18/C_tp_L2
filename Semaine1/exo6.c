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

int pair(int nb);
int impair(int nb);

int pair(int nb)
{
	if (nb == 0)
		return 1;
	if (nb == 1)
		return 0;
	return impair(nb - 1);
}

int impair(int nb)
{
	if (nb == 1)
		return 1;
	if (nb == 2)
		return 0;
	return pair(nb - 1);
}

int main(int argc, const char *argv[])
{
	printf("%d ", pair(atoi(argv[1])));
	printf("%d", impair(atoi(argv[1])));
	return 0;
}
