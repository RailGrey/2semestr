#include <iostream>

int help(int **data, int l_idx, int r_idx, int pivot) {
    while(true) {
        while (data[l_idx][1] < pivot) l_idx++;
        while (pivot < data[r_idx][1]) r_idx--;
        if (r_idx <= l_idx)
            return r_idx;
        int tmp_1 = data[l_idx][1];
        int tmp_0 = data[l_idx][0];
        data[l_idx][1] = data[r_idx][1];
        data[r_idx][1] = tmp_1;
        data[l_idx][0] = data[l_idx][0];
        data[l_idx][0] = tmp_0;
        l_idx++;
        r_idx--;
    }
}

void q_sort(int **data, int l_idx, int r_idx) {
    if (l_idx >= r_idx) {
        return;
    }
    int split_idx = help(data, l_idx, r_idx, data[l_idx + (r_idx - l_idx) / 2][1]);
    q_sort(data, l_idx, split_idx);
    q_sort(data, split_idx + 1, r_idx);
}

int main() {
    int n;
    std::cin >> n;
    int **array = new int *[n];
    for (int i = 0; i < n; i++) {
        array[i] = new int [2];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> array[i][0] >> array[i][1];
    }
    q_sort(array, 0, n-1);
    int count = 0, curr_t = 0;
    for (int i = 0; i < n; i++) {
        if (array[i][0] >= curr_t) {
            curr_t =  array[i][1];
            count++;
        }
    }
    std::cout << count << std::endl;
    return 0;
}

