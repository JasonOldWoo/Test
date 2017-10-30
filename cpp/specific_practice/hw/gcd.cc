#include <iostream>

int gcd(int a, int b)
{
    while (a != b) {
        if (a > b) {
            a = a - b;
        } else {
            b = b - a;
        }
    }
    
    return a;
}

int main(int argc, char* argv[])
{
    int a = 0;
    int b = 0;
    int g = 0;
    std::cin >> a;
    std::cin >> b;
    g = gcd(a, b);
    std::cout << (a / g * b) << std::endl;	// 要防止溢出
    return 0;
}
