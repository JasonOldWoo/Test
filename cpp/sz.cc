#include <iostream>
#include <list>

struct Info_t {
	char szID[20];
};

typedef std::list<Info_t> LIST_INFO;

int main()
{
	Info_t stInfo = {"Catch word!"};
	LIST_INFO listInfo;
	listInfo.push_back(stInfo);
	for (LIST_INFO::iterator it = listInfo.begin(); it != listInfo.end(); it++)
		std::cout << (*it).szID << '\n';
	return 0;
}
