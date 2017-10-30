#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

int main()
{
	pthread_mutex_t mtx;
	pthread_mutex_init(&mtx, 0);
	int nIndex = 0;
	struct timeval s;
	struct timeval e;
	gettimeofday(&s, 0);
	for (unsigned int i = 0; i < 1000000; i++)
	{
		__sync_add_and_fetch(&nIndex, 1);
	}
	gettimeofday(&e, 0);
	printf("elapsed: %lu\n", (e.tv_sec - s.tv_sec) * 1000 + (e.tv_usec - s.tv_usec));
	nIndex = 0;
	for (unsigned int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mtx);
		nIndex++;
		pthread_mutex_unlock(&mtx);
	}
	gettimeofday(&s, 0);
	printf("elapsed: %lu\n", (s.tv_sec - e.tv_sec) * 1000 + (s.tv_usec - e.tv_usec));
	pthread_mutex_destroy(&mtx);
	return 0;
}
