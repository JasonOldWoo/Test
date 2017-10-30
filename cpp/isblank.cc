#include <cctype>
#include <iostream>

int main()
{
	char b = -1;
	std::cout << std::isblank(static_cast<int>(b)) << '\n';
	std::cout << b << '\n';
	return 0;
}
