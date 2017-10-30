#include <iostream>
#include <unistd.h>

int main()
{
	int T = 0;
	int count = 0;
	while (!std::cin.eof()) {
		std::cin >> T;
		count++;
		::sleep(1);
	}
	std::cout << count << std::endl;

	return 0;
}
