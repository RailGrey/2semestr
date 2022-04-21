#include <iostream>


int main() {
    int s, count = 0, tmp_s = 0, i = 4;
    std::cin >> s;
    int array[5] = {1, 5, 25, 50, 100};
    while (tmp_s < s) {
        if ((tmp_s + array[i]) <= s) {
            tmp_s += array[i];
            count++;
        } else {
            i--;
        }
    }
    std::cout << count << std::endl;
    return 0;
}

