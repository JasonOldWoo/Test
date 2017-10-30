#include <stdio.h>

void swap(int* a, int* b)
{
	if (a != b) {
		int tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

void print (int* a, int len)
{
	int i = 0;
	for (i = 0; i < len; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}


