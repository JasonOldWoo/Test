#include <stdint.h>
#include <iostream>
#include <map>
#include <typeinfo>
#include <cstring>
#include <memory>

std::map<size_t, char>::value_type ini = {typeid (int).hash_code(), 'i'};
std::map<char, size_t>::value_type rini = {'i', typeid(int).hash_code()};

std::map<size_t, char> g_TypeIdMap = {ini};
std::map<char, size_t> g_rTypeIdMap = {rini};

#define REG_STRUCT(TYPE)	\
struct Config_##TYPE { \
public:	\
	Config_##TYPE()	\
	{

#define REG_INT32(m)	\
		std::unique_ptr<char[]> uq_data_##m(new char[5]);	\
		::memset(&uq_data_##m[0], 0x0, 5);	\
		uq_data_##m[0] = g_TypeIdMap[typeid(int).hash_code()];	\
		m_.insert(std::make_pair(#m, std::move(uq_data_##m)));

#define REG_END()	\
	}	\
	std::map<std::string, std::unique_ptr<char[]> > m_;	\
};

REG_STRUCT(Test)
REG_INT32(fuck)
REG_END()

int main(int argc, char* argv[])
{
	Config_Test t;
	std::strcpy(&t.m_["fuck"][0], "Hell");

	std::cout << t.m_["fuck"].get() << std::endl;
}
