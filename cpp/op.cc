#include <iostream>
class A
{
public:
	__attribute__((always_inline)) long operator () () { return 1000; }
};

int main()
{
	A c;
	std::cout << c() << '\n';
	return 0;
}
