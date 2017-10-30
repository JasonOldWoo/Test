#include <stdint.h>

class CA
{
public:
	CA& operator<<(unsigned short n) {return *this;}
	CA& operator<<(uint16_t n) {return *this;}
};

int main()
{
	CA a;
	return 0;
}
