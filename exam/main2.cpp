#include <iostream>

void peaks(int *data, int size) {
    if (size <= 2) {
        return;
    }
    int prev = data[0];
    int curr;
    int first;
    bool flag = true;
    for (int i = 1; i < size; i++) {
        if (flag && (data[i] != prev)) {
            flag = false;
            curr = data[i];
            first = i;
        }
        else if (!flag && (data[i] < curr) && (prev < curr)) {
            std::cout << "pos: " << first << " peak " << curr << std::endl;
            prev = curr;
            curr = data[i];
            first = i;
        } else if (data[i] != data[i-1]) {
            prev = curr;
            curr = data[i];
            first = i;
        }
    }
}

int main() {
    /*int size;
    std::cin >> size;
    int* mountains = new int[size];
    for (int i = 0; i < size; i++) {
        std::cin >> mountains[i];
    }*/
    int data[] = {18, 18, 10, -3, -4, 15, 15, -1,
                  13, 17, 11, 4, 18, -4, 19, 4, 18, 10, -4,
                  8, 13, 9, 16, 18, 6, 7};
    peaks(data, 26);
    {
        int data[4]= {1, 1, 1, 1};
        peaks(data,4);
    }
    return 0;
}

