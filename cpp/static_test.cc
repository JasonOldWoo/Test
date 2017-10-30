#include <stdio.h>

class A
{
	static A* m_pA;
public:
	static A* Instance()
	{
		printf("A:%s\n", __FUNCTION__);
		if (!m_pA) return (m_pA = new A);
		else return m_pA;
	}
};

A* A::m_pA = 0;

static A* GetHandle()
{
	printf("1\n");
	static A* szHandle[] =
	{
		A::Instance()
	};
	printf("2\n");
	return szHandle[0];
}

int main()
{
	printf("%p\n", GetHandle());
	return 0;
}
