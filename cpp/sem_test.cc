#include <pthread.h>
#include <semaphore.h>

sem_t g_sem;

void* ThreadProc(void*)
{
	sem_wait(&g_sem);
}

int main()
{
	sem_init(&g_sem, 0, 0);
	pthread_t tid;
	pthread_create(&tid, 0, &ThreadProc, 0);
	sem_post(&g_sem);
	sem_destroy(&g_sem);
	pthread_join(tid, 0);

	return 0;
}
