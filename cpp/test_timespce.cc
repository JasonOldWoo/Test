#include <time.h>
#include <iostream>

int main()
{
	timespec tTs;
	clock_gettime(CLOCK_REALTIME, &tTs);
	std::cout << tTs.tv_sec << " " << tTs.tv_nsec << '\n';
	return 0;
}
