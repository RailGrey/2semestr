#include <iostream>

int lineal(int const array[], int size, int found) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] == found) {
            count = i + 1;
        }
    }
    return count;
}

int bin_found(int const array[], int size, int found) {
    int count = 0, len = size, current_position = size / 2;
    bool flag = true;
    while (len != 1) {
        count++;
        if (array[current_position] == found) {
            flag = false;
            break;
        } else if (array[current_position] > found) {
            len = len / 2;
            current_position -= len / 2;
        } else {
            len = len - len / 2;
            current_position += len / 2;
        }
    }
    if (flag) {
        return 0;
    } else {
        return count;
    }
}

int main() {
    int const size = 7;
    int array[size];
    for (int i = 0; i < size; i++) std::cin >> array[i];
    int found, count;
    std::cin >> found;
    count = lineal(array, size, found);
    if (count == 0) {
        std::cout << "No such element" << std::endl;
    } else {
        std::cout << count << std::endl;
    }
    count = bin_found(array, size, found);
    if (count == 0) {
        std::cout << "No such element";
    } else {
        std::cout << count;
    }
    return 0;
}
