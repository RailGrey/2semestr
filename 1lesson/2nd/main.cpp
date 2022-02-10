#include <iostream>

//bool is_open_(cha)

int main() {
    int n;
    std::cin >> n;
    char tmp;
    int counter = 0;
    for (int i = 0; i < n && counter >= 0; i++) {
        std::cin >> tmp;
        if (tmp == '(') {
            counter += 1;
        } else {
            counter -= 1;
        }
    }
    if (counter == 0) {
        std::cout << "All right" << std::endl;
    } else {
        std::cout << "Wrong" << std::endl;
    }
    return 0;
}
