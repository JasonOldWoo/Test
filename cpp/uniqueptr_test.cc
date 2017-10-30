#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <iostream>

struct Foo {
	Foo() { std::cout << "Foo\n"; str_ = "Hello, world!"; }
	~Foo() { std::cout << "~Foo\n"; }
	void print() { std::cout << str_ << std::endl; }
private:
	std::string str_;
};

void func(std::unique_ptr<Foo>& p) {
	p->print();
}

int main()
{
	//std::cout << "Creating new Foo...\n";
	//std::unique_ptr<Foo> p2(new Foo);
	//{
	//	std::unique_ptr<Foo> p1;
	//	p1 = std::move(p2);
	//	p2 = std::move(p1);

	//	std::cout << "About to leave scope...\n";
	//}

	//std::cout << "About to leave program...\n";
	//std::unique_ptr<Foo> p(new Foo);
	//func(p);
	//std::cout << "About to leave program....\n";
	std::map<int, std::shared_ptr<std::map<int, Foo> > > m;
	Foo foo;
	{
		std::shared_ptr<std::map<int, Foo> > p = std::make_shared<std::map<int, Foo> >();
		m[11] = p;
	}
	(*m[11])[2] = foo;
	m.clear();
	std::cout << "about to leave program....\n";
}
