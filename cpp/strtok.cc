// strings and c-strings
#include <iostream>
#include <cstring>
#include <string>
#include <pthread.h>
#include <unistd.h>

void* thread1(void* args)
{
	char* p = (char*) args;
	char* tok = std::strtok(p, " ");
	while (tok != 0)
	{
		std::cout << tok << std::endl;
		tok = std::strtok(NULL, " ");
		sleep(1);
	}
	return 0;
}

int main ()
{
  char s1[] = "Please split this sentence into tokens";
  char s2[] = "xxxx yyyy zzzz aaaa bbbb sjsjjs";
  pthread_t tid1, tid2;
  pthread_create(&tid1, 0, &thread1, s1);
  //pthread_create(&tid2, 0, &thread1, s2);
  pthread_join(tid1, 0);
  //pthread_join(tid2, 0);

  return 0;
}
