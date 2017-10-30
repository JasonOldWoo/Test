#include <string.h>
#include <iostream>

int main()
{
	char szBuffer[5] = "Hell";
	std::cout << szBuffer << '\n';
	strncpy(szBuffer, "ha", 2);
	std::cout << szBuffer << '\n';
	return 0;
}
