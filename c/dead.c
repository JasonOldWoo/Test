#include <unistd.h>
#include <pthread.h>

void* routine1(void* arg)
{
	while (1) {
		usleep(50);
	}
}

void* routine2(void* arg)
{
	while (1) {
		usleep(200);
	}
}

int main()
{
	pthread_t t1 = 0;
	pthread_t t2 = 0;

	pthread_create(&t1, NULL, &routine1, NULL);
	pthread_create(&t2, NULL, &routine2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}
