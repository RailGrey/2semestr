#include <iostream>

int main() {
    int n;
    std::cin >> n; //print 1 string
    for (int i = 0; i < n; i++) {
        std::cout << char(65 + i);
    }
    for (int i = 0; i < n - 1; i++) {
        std::cout << char(65 + n - 2 - i);
    }
    std::cout << std::endl;
    for (int i = 1; i < n; i++) { //print others strings
        for (int j = 0; j < n - i; j++) {
            std::cout << char(65 + j);
        }
        for (int j = 0; j < 2 * i - 1; j++) {
            std::cout << " ";
        }
        for (int j = 0; j < n - i; j++) {
            std::cout << char(65 + n - 1 - i - j);
        }
        std::cout << std::endl;
    }
    return 0;
}
