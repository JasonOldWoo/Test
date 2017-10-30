#include <time.h>
#include <stdio.h>
#include <string.h>

int main()
{
	struct tm tTm;
	memset(&tTm, 0x0, sizeof (tTm));
	tTm.tm_year = 2017 - 1900;
	tTm.tm_mon = 8;
	tTm.tm_mday = 20;
	time_t nT = mktime(&tTm);
	time_t nN = time(NULL);
	printf("nT: %u, nN: %u, nD: %u\n", nT, nN, nN - nT);
	printf("%d\n", sizeof (time_t));
	return 0;
}
