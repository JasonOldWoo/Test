#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class Solution {
public:
	void replaceSpace(char *str, int length) {
        int str_len = strlen(str);
        if (str_len >= length) {
            return ;	// exception
        }

				std::string sstr;
				sstr.reserve(1024 * 1024 * 512);
				std::cout << "length: " << sstr.length() << std::endl;
				std::cout << "size: " << sstr.size() << std::endl;
				std::cout << "capacity: " << sstr.capacity() << std::endl;
				sstr.append("%20");
				std::cout << sstr.c_str() << std::endl;
				std::cout << "length: " << sstr.length() << std::endl;
				std::cout << "capacity: " << sstr.capacity() << std::endl;
        char* cur = str;
        char* pre = cur;

        while (*cur) {
            if (' ' == *cur) {
                pre = cur + 1;
            }
            cur ++;
						//std::cout << sstr << std::endl;
        }
	}
};

int main()
{
	char str[20] = "Who I am";
	Solution s;
	s.replaceSpace(str, 20);
	std::cout << str << std::endl;
	return 0;
}
