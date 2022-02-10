#include <iostream>

int reverse(int &a) {
    int b = 0;
    while (a != 0) {
        b = b * 10 + a % 10;
        a = a / 10;
    }
    a = b;
    return b;
}

int main() {
    int a;
    std::cin >> a;
    int &b = a;
    reverse(a);
    std::cout << a << " " << b << std::endl;
    return 0;
}
