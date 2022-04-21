#include <iostream>
#include <random>

void print(int array[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void min(int &a, int &b, int &c) {
    if (b <= a && b <= c) {
        swap(a, b);
    } else if (c <= a && c <= b) {
        swap(a, c);
    }
}

void min(int &a, int &b) {
    if (b <= a) {
        swap(a, b);
    }
}

void heapify(int data[], int j, int size) {
    if (j < 0) {
        return;
    }
    if (2*j+2 <= size) {
        min(data[j], data[2*j+1], data[2*j+2]);
    } else {
        min(data[j], data[2*j+1]);
    }
    return heapify(data, j-1, size);
}

void tree_sort(int data[], int n) {
    for (int i = 0; i < n; i++) {
        heapify(data, (n-i)/2-1, n-i-1);
        print(data, n);
        swap(data[0], data[n-i-1]);
    }
}

void fill(int data[], int n, int seed) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(0, 100);
    for (int i = 0; i < n; i++) {
        data[i] = dist(rng);
    }
}

int main() {
    int n;
    std::cin >> n;
    int *data = new int[n];
    fill(data, n, 12);
    print(data, n);
    tree_sort(data, n);
    print(data, n);
    delete []data;
    return 0;
}

