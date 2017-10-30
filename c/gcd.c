#include <stdio.h>

#define abs(a) ((a) > 0 ? (a) : -(a))
#define min(a, b) ((a) < (b) ? (a) : (b))

int gcd(int a, int b)
{
	printf("%d, %d\n", a, b);
	if (a == b) return a;
	return gcd(abs(a - b), min(a, b));
}

int main()
{
	int a = 704, b = 826;
	int g = gcd(a, b);
	printf("gcd: %d\n", g);

	return 0;
}
