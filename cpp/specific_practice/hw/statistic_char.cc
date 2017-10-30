#include <iostream>
#include <string>

int count_char(std::string& str, char c)
{
    std::size_t found = str.find_first_of(c);
		int count = 0;
    while (std::string::npos != found) {
        count++;
        found = str.find_first_of(c, found + 1);
    }

		return count;
}

int main(int argc, char* argv[])
{
    std::string str;
    char c = 0;
    std::getline(std::cin, str);
    std::cin >> c;
    int count = count_char(str, c);
		if (c >= 'A' && c <= 'Z') {
			count += count_char(str, c + 'a' - 'A');
		} else if (c >= 'a' && c <= 'z') {
			count += count_char(str, c + 'A' - 'a');
		}
    std::cout << count << std::endl;
		return 0;
}
