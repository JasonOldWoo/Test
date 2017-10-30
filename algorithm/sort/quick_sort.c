#include "utils.h"

int partition(int* a, int left, int right, int pivot_index)
{
	int pivot_value = a[pivot_index];
	swap(a + pivot_index, a + right);
	int store_index = left;
	int i = 0;
	for (i = left; i < right; i++) {
		if (a[i] < pivot_value) {
			swap(a + i, a + store_index);
			store_index++;
		}
	}
	swap(a + right, a + store_index);
	return store_index;
}

void quick_sort(int* a, int left, int right)
{
	if (right > left) {
		int pivot_index = (right + left) / 2;
		pivot_index = partition(a, left, right, pivot_index);
		quick_sort(a, left, pivot_index);
		quick_sort(a, pivot_index + 1, right);
	}
}

int main()
{
	int a[] = {928, 3, 7, 927, 8, 5, 2, 8726, 1, 9, 927, 5, 4};
	quick_sort(a, 0, sizeof (a) / sizeof (int) - 1);
	print(a, sizeof (a) / sizeof (int));

	return 0;
}
