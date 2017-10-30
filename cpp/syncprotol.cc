#include <stdio.h>
#include <stdint.h>

int main()
{
	int nMsg = 1;
	printf("%d\n", __sync_add_and_fetch(&nMsg, 1));

	int32_t nIndex = 0;
	printf("before sync: %d\n", __sync_fetch_and_or(&nIndex, (nMsg - 1)));
	printf("after sync: %d\n", nIndex);
	return 0;
}
