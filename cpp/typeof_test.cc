#include <string>
#include <iostream>
#include <typeinfo>

int main()
{
	int a;
	std::cout << typeid (a).name() << std::endl;
	std::cout << typeid (int).name() << std::endl;
	std::cout << typeid (a).hash_code() << std::endl;
	char s[6];
	std::cout << typeid (s).name() << std::endl;
	std::cout << typeid (s).hash_code() << std::endl;
	char* p;
	std::cout << typeid (p).name() << std::endl;
	std::cout << typeid (p).hash_code() << std::endl;
	std::cout << typeid (std::string).name() << std::endl;
	return 0;
}
