#include <iostream>
#include <memory>
#include <string>
#include <cstring>

struct Foo {
	Foo() { std::cout << "Foo\n"; str_ = "Hello, world!"; }
	~Foo() { std::cout << "~Foo\n"; }
	void print() { std::cout << str_ << std::endl; }
private:
	std::string str_;
};

struct B : public Foo {

};

int main()
{
	//std::shared_ptr<Foo> foo = std::make_shared<Foo>();
	//{
	//	//std::shared_ptr<Foo> foo2 = foo;
	//	//std::shared_ptr<Foo> foo2 = std::move(foo);
	//	std::cout << "About to leave scope" << std::endl;
	//}
	//std::cout << "About to leave program" << std::endl;

	std::unique_ptr<char[]> p(new char[5]);
	::memcpy(&p[0], "Hell", 5);
	std::cout << &p[0] << std::endl;

	return 0;
}
