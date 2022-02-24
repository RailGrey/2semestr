#include <iostream>
#include <random>

int walk(int x, int y, int size, int seed) {
    std::mt19937 rng(seed); // hardcoded seed
    std::uniform_int_distribution<int> dist(0, 3);
    int count = 0, rotate;
    while (x >= 0 && x < size && y >= 0 && y < size) {
        count++;
        rotate = dist(rng);
        switch (rotate) {
            case 0: x++; break;
            case 1: x--; break;
            case 2: y++; break;
            case 3: y--; break;
        }
    }
    return count;
}

int main() {
    float sum;
    for (int size = 5; size < 1000; size++) {
        sum = 0;
        for (int i = 0; i < 20; i++) {
            sum += walk(size/2, size/2, size, i);
        }
        std::cout << sum / 20 << ", ";
        if (size % 10 == 0) {
            std::cout << '\n';
        }
    }
    return 0;
}
