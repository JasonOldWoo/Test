#include <stdio.h>
#include <unistd.h>

class B
{
public:
	B() {printf("B\n");}
};

class A
{
	static A* m_pA;
	static B m_clsB;
public:
	static A* Instance()
	{
		printf("A:%s\n", __FUNCTION__);
		if (!m_pA) return (m_pA = new A);
		else return m_pA;
	}
	static B* InstanceB()
	{
		printf("A:%s\n", __FUNCTION__);
		return &m_clsB;
	}
};

A* A::m_pA = 0;
B A::m_clsB;

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
	sleep(1);
	printf("%p\n", GetHandle());
	printf("%p\n", A::InstanceB());
	return 0;
}
