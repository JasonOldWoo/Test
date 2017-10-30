#include "utils.h"

void merge_sort_recursive(int* a, int* r, int s, int e)
{
	if (s >= e) return ;

	int len = e - s;
	int m = (len >> 1) + s;
	int s1 = s;
	int e1 = m;
	int s2 = m + 1;
	int e2 = e;

	merge_sort_recursive(a, r, s1, e1);
	merge_sort_recursive(a, r, s2, e2);

	int k = s;
	while (s1 <= e1 && s2 <= e2) {
		r[k++] = a[s1] < a[s2] ? a[s1++] : a[s2++];
	}

	while (s1 <= e1) {
		r[k++] = a[s1++];
	}

	while (s2 <= e2) {
		r[k++] = a[s2++];
	}

	for (k = s; k <= e; k++) {
		a[k] = r[k];
	}

	print(a, e - s + 1);
}

void merge_sort(int* a, int len)
{
	int r[len];
	merge_sort_recursive(a, r, 0, len - 1);
}

int main()
{
	int arr[] = { 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
	int len = sizeof (arr) / sizeof (int);
	merge_sort(arr, len);
	print(arr, len);
	return 0;
}
