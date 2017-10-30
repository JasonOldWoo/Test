#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <cstdint>
#include <cstdio>

typedef std::pair<std::string, int16_t> PAIR_t;

bool compare_pair(const PAIR_t& f, const PAIR_t& s)
{
	char ot = f.second >> 8;
	char st = s.second >> 8;
	char sot = 0;
	char sst = 0;
	switch (ot)  {
		case 'i' : sot = 4; break ;
		case 'b' : sot = 1; break ;
		default: break;
	}
	switch (st) {
		case 'i' : sst = 4; break ;
		case 'b' : sst = 1; break ;
	}
	return sot < sst;
}

int main()
{
	std::list<PAIR_t> l;
	l.push_back(PAIR_t("Pap", (((short) 'i') << 8)));
	l.push_back(PAIR_t("Bob", (((short) 'b') << 8)));
	l.push_back(PAIR_t("Amy", (((short) 'i') << 8)));
	l.push_back(PAIR_t("Jim", (((short) 'i') << 8)));
	for (auto& it : l) {
		printf("%s: 0x%x\n", it.first.c_str(), it.second);
	}
	printf("\n");
	l.sort(compare_pair);
	for (auto& it : l) {
		printf("%s: 0x%x\n", it.first.c_str(), it.second);
	}
}
