#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int nIndex1 = 0;
int nIndex2 = 0;
pthread_mutex_t mtx;

void* routine_synclang(void*)
{
	for (unsigned int i = 0; i < 2000000; i++)
	{
		__sync_add_and_fetch(&nIndex1, 1);
	}
	return NULL;
}

void* routine_mutex(void*)
{
	for (unsigned int i = 0; i < 2000000; i++)
	{
		pthread_mutex_lock(&mtx);
		nIndex2++;
		pthread_mutex_unlock(&mtx);
	}
	return NULL;
}

int main()
{
	pthread_mutex_init(&mtx, 0);
	struct timeval s;
	struct timeval e;
	
	pthread_t thrd1;
	pthread_create(&thrd1, NULL, routine_synclang, NULL);
	usleep(20);
	gettimeofday(&s, 0);
	for (unsigned int i = 0; i < 1000000; i++)
	{
		__sync_add_and_fetch(&nIndex1, 1);
	}
	gettimeofday(&e, 0);
	printf("sync elapsed(usec): %lu\n", ((e.tv_sec - s.tv_sec) * 1000000 + (e.tv_usec - s.tv_usec)));
	pthread_join(thrd1, NULL);
	
	pthread_t thrd2;
	pthread_create(&thrd2, NULL, routine_mutex, NULL);
	usleep(20);
	gettimeofday(&e, 0);
	for (unsigned int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mtx);
		nIndex2++;
		pthread_mutex_unlock(&mtx);
	}
	gettimeofday(&s, 0);
	printf("mutex elapsed(usec): %lu\n", ((s.tv_sec - e.tv_sec) * 1000000 + (s.tv_usec - e.tv_usec)));
	pthread_join(thrd2, NULL);
	pthread_mutex_destroy(&mtx);
	return 0;
}
