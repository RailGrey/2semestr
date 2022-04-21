#include <iostream>

unsigned get_power(unsigned long long n) {
    bool flag = true;
    unsigned long long i;
    unsigned power = 0;
    while (flag && (n > 1)) {
        i = n - n / 2;
        if (((n - i) ==  i)) {
            power++;
        } else {
            flag = false;
        }

        n = i;
    }
    return power;
}

int main() {
    unsigned long long n;
    unsigned long long count = 0;
    std::cin >> n;
    while (n > 0) {
        count += n / 2;
        n = n / 2;
    }
    std::cout << count;
    return 0;
}


