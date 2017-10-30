#include <list>
#include <string>
#include <iostream>

typedef struct
{
	int id;
	std::string str;
} Node_t;

int main()
{
	Node_t tTmp;
	std::list<Node_t> l;
	l.assign(0, tTmp);
	std::cout << l.size() << "\n";
	std::list<Node_t>::iterator it;
	for (it = l.begin(); it != l.end(); it++)
	{
		(*it).id = 1;
		(*it).str = "dhsaiuh";
		std::cout << (*it).id << " " << (*it).str << "\n";
	}

	return 0;
}
