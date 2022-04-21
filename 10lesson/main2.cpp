#include <iostream>


int Tribonachi(int n) {
    int *array = new int[n+1];
    array[0] = 0;
    array[1] = 1;
    array[2] = 1;
    for (int i = 3; i < (n + 1); i++) {
        array[i] = array[i - 1] + array[i - 2] + array[i - 3];
    }
    return array[n];
}

int main() {
    std::cout << Tribonachi(37);
    return 0;
}
