#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    std::string str;
		std::getline(std::cin, str);
    std::size_t r = str.find_last_not_of(" ");
    std::size_t l = str.find_last_of(" ", r);
    if (l != std::string::npos) {
    	std::cout << r - l << std::endl;
    } else {
        std::cout << r + 1 << std::endl;
    }
		return 0;
}
