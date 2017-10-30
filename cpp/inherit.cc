#include <iostream>

class virtual_base
{
public:
    virtual void Test() = 0;
};

class A
{
public:
    //virtual void Test() {std::cout << "A" << std::endl;}
    void Test() {std::cout << "A" << std::endl;}
};

class B
{
public:
    virtual void Test() {std::cout << "B" << std::endl;}
};

class Derive : public A
{
public:
    //virtual void Test() {std::cout << "Derive" << std::endl;}
    virtual void Test() {std::cout << "Derive" << std::endl;}
};

int main()
{
    A* p = new Derive();
    p->Test();
    delete p;

    return 0;
}
