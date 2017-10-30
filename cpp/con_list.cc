#include <list>
#include <string>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

std::list<std::string> g_list;

void* push_thread(void*)
{
	int count = 100000;
	while (count--)
	{
		g_list.push_back("husdhaisdhu");
		::usleep(20);
	}
}

int main()
{
	pthread_t tid;
	pthread_create(&tid, 0, &push_thread, 0);
	int count = 100000;
	while (count--)
	{
		g_list.push_back("shduygdfhguysgyq");
		::usleep(18);
	}
	pthread_join(tid, 0);
	printf("%lu\n", g_list.size());
	//for (std::list<std::string>::iterator it = g_list.begin(); it != g_list.end(); it++)
	//{
	//	//printf("%s\n", (*it).c_str());
	//}
	return 0;
}
