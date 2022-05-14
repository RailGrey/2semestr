#include <iostream>

int help_LCS(char *a, char *b, int i, int j, int **memo) {
    if ((i == 0) || (j == 0)) {
        return 0;
    }
    if (memo[i][j] >= 0) {
        return memo[i][j];
    } else if (a[i] == b[j]) {
        memo[i][j] = help_LCS(a, b, i-1, j-1, memo) + 1;
        return memo[i][j];
    } else {
        memo[i][j] = std::max(help_LCS(a, b, i-1, j, memo), help_LCS(a, b, i, j-1, memo));
        return memo[i][j];
    }
}

int LCS(char *a, char *b, int i, int j) {
    int **memo = new int*[i+1];
    for (int f = 0; f < i+1; f++) {
        memo[f] = new int[j+1];
    }
    for (int k = 0; k < i+1; k++) {
        for (int l = 0; l < j+1; l++) {
            memo[k][l] = -1;
        }
    }
    int result = help_LCS(a, b, i, j, memo);
    for (int k = 0; k < i + 1; k++) {
        delete []memo[k];
    }
    delete []memo;
    return result;
}

int main() {
    int n, m;
    std::cin >> n;
    char *a = new char[n+1];
    for (int i = 1; i < n + 1; i++) {
        std::cin >> a[i];
    }
    std::cin >> m;
    char *b = new char[m+1];
    for (int i = 1; i < m + 1; i++) {
        std::cin >> b[i];
    }
    std::cout << "Similar " << LCS(a, b, n, m) << "/" << n;
    delete []a;
    delete []b;
    return 0;
}