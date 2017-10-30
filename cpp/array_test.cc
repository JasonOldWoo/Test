#include <array>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>

struct timeval tv_;

static void initTick()
{
	gettimeofday(&tv_, NULL);
}

static uint64_t getTick()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	time_t secv = tv.tv_sec - tv_.tv_sec;
	suseconds_t usecv = tv.tv_usec - tv_.tv_usec;
	return (secv * 1000 + usecv / 1000);
}
#define SIZE 10000000UL

int main()
{
	initTick();
	printf("00\n");
	//std::vector<int> sv;
	//sv.reserve(SIZE);
	//printf("11 vector max size: %lu\n", sv.max_size());
	std::array<int, SIZE> sa;
	printf("22\n");
	int* ba = new int[SIZE];

	while (1) {
		printf("\n\n\n\n");
		uint64_t s = getTick();
		for (int i = 0; i < SIZE; i++) {
			ba[i] = i;
		}
		uint64_t e = getTick();
		printf("builtin array elapsed: %lu\n", e - s);
		sleep(1);
		s = getTick();
		for (int i = 0; i < SIZE; i++) {
			sa[i] = i;
		}
		e = getTick();
		printf("std::array elapsed: %lu\n", e - s);
		sleep(1);
	//	s = getTick();
	//	for (int i = 0; i < SIZE; i++) {
	//		sv[i] = i;
	//	}
	//	e = getTick();
	//	printf("std::vector elapsed: %lu\n", e - s);
	//	sleep(1);
	}
}
