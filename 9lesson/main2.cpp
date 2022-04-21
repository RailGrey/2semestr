#include <iostream>

int main() {
    int s, k, n;
    std::cin >> s >> k >> n;
    int *array = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }
    int curr_l = 0, i = 0, count = 0;
    bool flag = true;
    if (k >= s) {
        flag = false;
    }
    while (flag) {
        if((array[i] - curr_l) <= k) {
            i++;
            if ((array[i-1] + k) >= s) {
                flag = false;
                count++;
            } else if (i == n) {
                flag = false;
                count = -1;
            }
        } else {
            if (curr_l == array[i-1]) {
                flag = false;
                count = -1;
            } else {
                curr_l = array[i - 1];
                count++;
            }
            if ((curr_l + k) < n) {
                flag = false;
            }
        }
    }
    std::cout << count << std::endl;
    return 0;
}
