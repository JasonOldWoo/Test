#include <list>
#include <string>
#include <iostream>

typedef struct
{
	std::string f;
	int d;
} task_t;

int main()
{
	std::string f = "huisfdaf";
	std::list<task_t> l;
	/*
	l.push_back({f, 2});
	task_t* p = &(*l.begin());
	std::cout << p->d << " " << p->f << "\n";
	*/

	task_t t = {"uyfsdyfwqk", 1};
	return 0;
}
