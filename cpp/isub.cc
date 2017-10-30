#include <stdio.h>
#include <string.h>

int main()
{
	int len = -1;
	char buf[len];
	printf("%u %u\n", (unsigned int) len, sizeof (buf));
	memset(buf, 0x0, sizeof (buf));
	return 0;
}
