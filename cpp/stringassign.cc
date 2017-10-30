#include <string>
#include <iostream>
#include <string.h>

int main()
{
	char szVal[10] = {'k', 0, '\0', 'b', 'c'};
	std::string str;
	str.assign(szVal, 4);
	std::cout << str << "\n";
	std::cout << str.c_str() << "\n";
	std::cout << str.data() << "\n";
	std::cout << "size: " << str.size() << "\n";
	std::cout << "length: " << str.length() << "\n";
	std::cout << "capacity: " << str.capacity() << "\n";
	std::cout << "c_str len: " << strlen(str.c_str()) << "\n";

	str += "thx";
	std::cout << str << "\n";
	std::cout << str.c_str() << "\n";
	std::cout << str.data() << "\n";
	std::cout << "size: " << str.size() << "\n";
	std::cout << "length: " << str.length() << "\n";
	std::cout << "capacity: " << str.capacity() << "\n";
	std::cout << "c_str len: " << strlen(str.c_str()) << "\n";

	return 0;
}
