#include <sstream>
#include <string>
#include <iostream>

int main()
{
#if 0
	std::stringstream ss;
	ss << 10;
	ss << "#";
	ss << 12L;
	std::cout << ss.str() << '\n';
#else
	std::string st = "we find # is token##haha##";
	std::stringstream ss(st);
#endif

	std::string token;
	while (std::getline(ss, token, '#')) {
		std::cout << token << '\n';
	}
	return 0;
}
