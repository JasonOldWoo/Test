#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	char* p = argv[0];
	int ret = access(p, R_OK | X_OK);
	printf("%s access: %d\n", p, ret);
	return 0;
}
