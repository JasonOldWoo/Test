#include <iostream>
class  A
{
public:
	virtual ~A() {std::cout << "~A" << std::endl;}
};


class B : public A
{
public:
	virtual ~B() {std::cout << "~B" << std::endl;}
};

class C : public B
{
public:
	virtual ~C() {std::cout << "~C" << std::endl;}
};

int main()
{
	A* p = new B;
	delete p;	// ~B\n~A
	A* p2 = new C;
	delete p2;
	return 0;
}
