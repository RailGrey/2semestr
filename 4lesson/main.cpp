#include <iostream>
#include <random>

int help(int data[], int l_idx, int r_idx, int pivot) {
    while(true) {
        while (data[l_idx] < pivot) l_idx++;
        while (pivot < data[r_idx]) r_idx--;
        if (r_idx <= l_idx)
            return r_idx;
        int tmp = data[l_idx];
        data[l_idx] = data[r_idx];
        data[r_idx] = tmp;
        l_idx++;
        r_idx--;
    }
}

void q_sort(int data[], int l_idx, int r_idx) {
    if (l_idx >= r_idx) {
        return;
    }
    int split_idx = help(data, l_idx, r_idx, data[l_idx + (r_idx - l_idx) / 2]);
    q_sort(data, l_idx, split_idx);
    q_sort(data, split_idx + 1, r_idx);
}

void print(int array[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
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
    fill(data, n, 34);
    print(data, n);
    q_sort(data, 0, n-1);
    print(data, n);
    delete []data;
    return 0;
}
