#include <iostream>
#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
#define _ATOMIC_INCREAMENT32(b) \
    __sync_add_and_fetch(&(b), 1)
#define _ATOMIC_DECREAMENT32(b) \
    __sync_sub_and_fetch(&(b), 1)
#define _ATOMIC_DECREASE32(b, c)	\
	__sync_sub_and_fetch(&(b), (c))
#define __FORCE_INLINE __attribute__((always_inline))
#elif defined(_MSC_VER)
#include <Windows.h>
#define _ATOMIC_INCREAMENT32(b) \
    InterlockedIncrement(&(b))
#define _ATOMIC_DECREAMENT32(b) \
    InterlockedDecrement(&(b))
#define _ATOMIC_DECREASE32(b, c)	\
	(unsigned int) InterlockedAdd((long*) &(b), (long) -(c))
#define __FORCE_INLINE __forceinline
#endif

#include <pthread.h>
#include <unistd.h>

static unsigned int s_index = 19999980U;
static const unsigned int s_k_max = 19999990U;
__FORCE_INLINE static unsigned int __NSDK_FetchIndex()
{
    if (s_index > s_k_max) return _ATOMIC_DECREASE32(s_index, 10U);
    else return _ATOMIC_INCREAMENT32(s_index);
}

int g_cc = 1000;

void* pthread_proc_1(void*)
{
	while (g_cc--) {
		std::cout << __NSDK_FetchIndex() << '\n';
		::usleep(100);
	}
	return 0;
}

void* pthread_proc_2(void*)
{
	while (g_cc--) {
		std::cout << __NSDK_FetchIndex() << '\n';
		::usleep(100);
	}
	return 0;
}

void* pthread_proc_3(void*)
{
	while (g_cc--) {
		std::cout << __NSDK_FetchIndex() << '\n';
		::usleep(100);
	}
	return 0;
}

void* pthread_proc_4(void*)
{
	while (g_cc--) {
		std::cout << __NSDK_FetchIndex() << '\n';
		::usleep(100);
	}
	return 0;
}

typedef void* (*pfunc)(void*);

int main()
{
	pfunc sz_func[4] = {&pthread_proc_1, &pthread_proc_2, &pthread_proc_3, &pthread_proc_4};
	pthread_t sz_tid[4];
	for (int n = 0; n < 4; n++) {
		::pthread_create(&sz_tid[n], 0, sz_func[n], 0);
	}
	for (int n = 0; n < 4; n++) {
		::pthread_join(sz_tid[n], 0);
	}
	return 0;
}
