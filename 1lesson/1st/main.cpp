#include <iostream>
#include <cmath>

bool is_simple(int a) {
    bool flag = true;
    for (int i = 2; i < std::sqrt(a) && flag; i++) {
        if (a % i == 0) {
            flag = false;
        }
    }
    return flag;
}

int length_of_number(int a) {
    int i = 0;
    while (a != 0) {
        a = a / 10;
        i++;
    }
    return i;
}

int power(int a, int b) {
    int tmp = 1;
    for (int i = 0; i < b; i++) {
        tmp *= a;
    }
    return tmp;
}


bool is_palindrom(int a) {
    int length = length_of_number(a);
    bool flag = true;
    int tmp1, tmp2, cr, cr2;
    for (int i = 0; i < length / 2 && flag; i++) {
        cr = power(10, length - i - 1);
        tmp1 = (a - a % cr - a / (cr * 10) * cr * 10) / cr;
        cr2 = power(10, i + 1);
        tmp2 = (a - a / cr2 * cr2) / (cr2 / 10);
        if (tmp1 != tmp2) {
            flag = false;
        }
    }
    return flag;
}

bool is_palindrom2(int a) {
    int length = length_of_number(a);
    int tmp;
    for (int i = 0; i < length / 2 + length % 2; i++) {
        tmp = a % 10;
        a = (a - tmp - power(10, length - 1 - 2 * i) * tmp) / 10;
    }
    return a == 0;
}

int main() {
    int n, tmp;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> tmp;
        if (is_simple(tmp)) {
            std::cout << "Simple" << std::endl;
        } else {
            std::cout << "Complex" << std::endl;
        }
        if (is_palindrom2(tmp)) {
            std::cout << "Palindrom" << std::endl;
        } else {
            std::cout << "Not Palindrom" << std::endl;
        }
    }
    return 0;
}
