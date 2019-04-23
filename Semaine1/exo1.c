#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, const char *argv[])
{
	int p;
	int denominateur;
	int res;
	int tour;

	tour = 1;
	denominateur = 1;
	while ((M_PI - p > res * 4) && (res * 4 > M_PI + p))
	{
		if (tour)
		{
			tour = 0;
			res += 1 / denominateur;
		}
		else
		{
			tour = 1;
			res -= 1 / denominateur;
		}
		denominateur += 2;
	}
	return 0;
}
