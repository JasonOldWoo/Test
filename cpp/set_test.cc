#include <iostream>
#include <list>
#include <set>

typedef struct
{
	int id;
	int index;
} Index_t;

bool KeyComp(Index_t a, Index_t b)
{
	return a.id < b.id;
}

struct CKeyComp
{
	bool operator() (const Index_t& l, const Index_t& r) const
	{return l.id < r.id;}
};

int main()
{
	std::list<Index_t> l;
	Index_t tM1 = {1,2};
	Index_t tM2 = {2, 5};
	Index_t tM4 = {4, 11};
	Index_t tM6 = {4, 4};
	l.push_back(tM1);
	l.push_back(tM2);
	l.push_back(tM4);
	l.push_back(tM6);
	std::set<Index_t, CKeyComp> s(l.begin(), l.end());
	Index_t tMt = {2,4};
	std::set<Index_t, CKeyComp>::iterator e = s.find(tMt);
	std::cout << (*e).id << " " << (*e).index << '\n';
	return 0;
}
