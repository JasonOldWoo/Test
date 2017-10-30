#include <iostream>
#include <string>
#include <list>

int main(int argc, char* argv[])
{
    while (!std::cin.eof()) {
        int T = 0;
        std::list<int> l;
        std::cin >> T;
        while (T--) {
            int num = 0;
            std::cin >> num;
            l.push_back(num);
        }
        l.sort();
        l.unique();
        for(const auto& item : l) {
            std::cout << item <<std::endl;
        }
    }
    
    return 0;
}
