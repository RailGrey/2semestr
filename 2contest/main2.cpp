#include <iostream>

int help(int *data, int l_idx, int r_idx, int pivot) {
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

void q_sort(int *data, int l_idx, int r_idx) {
    if (l_idx >= r_idx) {
        return;
    }
    int split_idx = help(data, l_idx, r_idx, data[l_idx + (r_idx - l_idx) / 2]);
    q_sort(data, l_idx, split_idx);
    q_sort(data, split_idx + 1, r_idx);
}

int Nails(int *a, int l) {
    q_sort(a, 0, l-1);
    int *memo = new int[l+1];
    if (l == 2) {
        return a[1] - a[0];
    }
    memo[2] = a[1] - a[0];
    memo[3] = a[2] - a[0];
    for (int i = 4; i < l+1; i++) {
        memo[i] = std::min(memo[i-1], memo[i-2]) + a[i-1] - a[i-2];
    }
    int result = memo[l];
    delete []memo;
    return result;
}

int main() {
    int l = 0;
    int *data = new int[100];
    while (std::cin >> data[l]) {
        l++;
    }
    std::cout << Nails(data, l);
    delete []data;
    return 0;
}

