#include <memory>
#include <iostream>
#include <list>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

struct Data
{
    Data() {std::cout << "Data constructor" << std::endl;}
    ~Data() {std::cout << "Data destructor" << std::endl;}
    char _rawData[128];
};
 
struct Foo {
    std::shared_ptr<Data> _ptr;
    int _len;
};

std::list<Foo> glstFoo;
pthread_t gthrdHandle;

void* routine(void* pArgs)
{
    (void) pArgs;
    std::cout << "threadid: " << pthread_self() << std::endl;
    std::list<Foo>::iterator iter = glstFoo.begin();
    while (iter != glstFoo.end()) {
        std::cout << (*iter)._ptr.get()->_rawData << std::endl;
        glstFoo.pop_front();
        iter = glstFoo.begin();
    }
    return NULL;
}

void start_routine(void)
{
    std::shared_ptr<Data> _ptr1(new Data);
    strcpy(_ptr1.get()->_rawData, "Hello, world!");
    Foo foo;
    foo._ptr = _ptr1;
    foo._len = 128;
    glstFoo.push_back(foo);
    glstFoo.push_back(foo);
    glstFoo.push_back(foo);
    glstFoo.push_back(foo);
    glstFoo.push_back(foo);
    glstFoo.push_back(foo);
    pthread_create(&gthrdHandle, NULL, routine, NULL);
}

void stop_routine(void)
{
    pthread_join(gthrdHandle, NULL);
}
 
int main()
{
    //std::shared_ptr<char> _ptr1(new char[128], std::default_delete<char[]>());
    start_routine();
    std::cout << "out of scope 1" << std::endl;
    stop_routine();
    std::cout << "out of scope 2" << std::endl;
}
