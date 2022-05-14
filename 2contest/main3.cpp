#include <iostream>



int Jumps(int *a, int l) {
    if (l <= 1) {
        return 0;
    }
    int *memo = new int[l];
    memo[0] = 0;
    memo[1] = std::abs(a[1] - a[0]);
    int i = 2, tmp1, tmp2;
    while (i < l) {
        memo[i] = std::min(memo[i-1] + std::abs(a[i] - a[i-1]), memo[i-2] + 3 * std::abs(a[i] - a[i-2]));
        i++;
    }
    return memo[l-1];
}

int main() {
    int n;
    std::cin >> n;
    int *data = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> data[i];
    }
    std::cout << Jumps(data, n);
    return 0;
}

