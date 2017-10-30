#include <deque>
#include <iostream>

struct MSG
{
	unsigned int msg;
	unsigned int wpa;
	unsigned int lpa;
	time_t time;
};

int main()
{
	std::deque<MSG> d(32);
	MSG msg = {1, 2, 4, time(NULL)};
	d.push_back(msg);
	std::cout << d.front().msg << std::endl;
	return 0;
}
