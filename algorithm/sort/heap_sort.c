#include "utils.h"
#include <stdlib.h>

void max_heapify(int* a, int s, int e)
{
	int dad = s;
	int son = dad * 2 + 1;

	while (son <= e) {
		if (son + 1 <= e && a[son] < a[son + 1]) {
			son ++;	// select bigger son
		}

		if (a[dad] > a[son]) {
			return ;
		} else {
			swap(a + dad, a + son);
			dad = son;
			son = dad * 2 + 1;	// find grandchild
		}
	}
}

void heap_sort(int* a, int len)
{
	int i;
	for (i = len / 2 - 1; i >= 0; i--) {
		max_heapify(a, i, len - 1);
		print(a, len);
	}

	printf("max max_heapify at first\n");

	for (i = len - 1; i > 0; i--) {
		swap(a, a + i);
		max_heapify(a, 0, i - 1);
		print(a, len);
	}
}

int main()
{
	int arr[] = { 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
	//int arr[] = { 3, 5, 3, 1, 8, 0, 6 };
	int len = (int) sizeof(arr) / sizeof(*arr);
	print(arr, len);
	printf("start heap sort\n");
	heap_sort(arr, len);
	return 0;
}
