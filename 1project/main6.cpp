#include <iostream>
#include <random>
#include <chrono>


float start_initialization(int field[50][50][3], int seed, int k) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(0, k);
    float counter = 0;
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            if (dist(rng) == 0) {
                field[i][j][0] = 1;
                counter++;
            } else {
                field[i][j][0] = 0;
            }
        }
    }
    return counter;
}

void initialization(int field[50][50][3]) {
    //gives direction for alive cells
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            if (field[i][j][0] == 1) {
                field[i][j][1] = 1;
            } else {
                field[i][j][1] = 0;
            }
        }
    }
}

void go (int field[50][50][3], int x, int y) {
    field[x][y][0] = 0; //1 - right, 2 - left, 3 - down, 4 - up
    int tmp = field[x][y][1];
    field[x][y][1] = 0;
    switch (tmp) {
        case 1: field[x+1][y][0] = 1; field[x+1][y][1] = 0; break;
        case 2: field[x-1][y][0] = 1; field[x-1][y][1] = 0; break;
        case 3: field[x][y+1][0] = 1; field[x][y+1][1] = 0; break;
        case 4: field[x][y-1][0] = 1; field[x][y-1][1] = 0; break;
    }
}

void thick_moment (int field[50][50][3], int x, int y) {
    if (field[x+1][y+1][0] == 1 && field[x+1][y+1][1] == field[x][y][1]) {
        field[x+1][y+1][2] = 1;
    } else if (field[x-1][y+1][0] == 1 && field[x-1][y+1][1] == field[x][y][1]) {
        field[x-1][y+1][2] = 1;
    } else if (field[x+1][y-1][0] == 1 && field[x+1][y-1][1] == field[x][y][1]) {
        field[x+1][y-1][2] = 1;
    } else if (field[x-1][y-1][0] == 1 && field[x-1][y-1][1] == field[x][y][1]) {
        field[x-1][y-1][2] = 1;
    }
}

int possibility (int field[50][50][3], int x, int y) {
    if (field[x][y][1] == 0) {
        return 2;
    }
    if (field[x+1][y][0] == 1) {
        if (field[x][y][1] == 1) {
            return 2;
        } else {
            return 1;
        }
    } else if (field[x-1][y][0] == 1) {
        if (field[x][y][1] == 2) {
            return 2;
        } else {
            return 1;
        }
    } else if (field[x][y+1][0] == 1) {
        if (field[x][y][1] == 3) {
            return 2;
        } else {
            return 1;
        }
    } else if (field[x][y-1][0] == 1) {
        if (field[x][y][1] == 4) {
            return 2;
        } else {
            return 1;
        }
    }
    return 0;
}

float machine(int field[50][50][3], int x, int y, int seed) {
    int tmp;
    float count = 0; //count of iterations when everything is stops
    bool flag = true;
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(1, 4);
    while (flag) {
        flag = false;
        count++;
        initialization(field);
        for (int i = 1; i < x - 1; i++) {
            for (int j = 1; j < y - 1; j++) {
                if (field[i][j][1] != 0) {
                    field[i][j][1] = dist(rng);
                }
                tmp = possibility(field, i, j);
                if (tmp == 0) {
                    thick_moment(field, i, j);
                    go(field, i, j);
                    flag = true;
                } else if (tmp == 1 && field[i][j][2] == 1) {
                    thick_moment(field, i, j);
                    go(field, i, j);
                    flag = true;
                    field[i][j][2] = 0;
                }
            }
        }
    }
    return count;
}

void print(int field[50][50][3]) {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            std::cout << field[i][j][0] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "----" << "\n";
}

void test(int field[50][50][3]) {
    field[3][3][0] = 1;
    field[3][3][1] = 1;
    field[4][4][0] = 1;
    field[4][4][1] = 1;

    field[6][6][0] = 1;
    field[7][7][0] = 1;
    field[6][6][1] = 3;
    field[7][7][1] = 2;
    print(field);
    machine(field, 50, 50, 1);
    print(field);
}

bool lineal(int x[1000], int y[1000], int size, int found_x, int found_y) {
    bool flag = true;
    for (int i = 0; i < size && flag; i++) {
        if (x[i] == found_x) {
            if (y[i] == found_y) {
                flag = false;
            }
        }
    }
    return flag;
}

void initialization_for_2_type (int x[1000], int y[1000], int size) {
    std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0, 49);
    bool flag = true;
    int x_c, y_c;
    for (int i = 0; i < 1000; i++) {
        x[i] = 0;
        y[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        flag = true;
        while (flag) {
            x_c = dist(rng);
            y_c = dist(rng);
            if (lineal(x, y, size, x_c, y_c)) {
                flag = false;
                x[i] = x_c;
                y[i] = y_c;
            }
        }
    }
}

int machine2 (int x[1000], int y[1000], int size) {
    std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0, 3);
    initialization_for_2_type(x, y, size);
    bool flag = true;
    int rotate, count = 0;
    while (flag) {
        flag = false;
        for (int i = 0; i < size; i++) {
            if (x[i] != 0 && y[i] != 0 && x[i] != 49 && y[i] != 49) {
                flag = true;
                count++;
                rotate = dist(rng);
                switch (rotate) {
                    case 0: x[i]++; break;
                    case 1: x[i]--; break;
                    case 2: y[i]++; break;
                    case 3: y[i]--; break;
                }
            }
        }
    }
    return count;
}

int main() {
    int type_of_model;
    std::cout << "To activate classic mode type 0, to activate mode without relation type 1." << '\n';
    std::cin >> type_of_model;
    if (type_of_model == 0) {
        int field[50][50][3] = {0}; //1,2 - coordinates, 3 - life, rotation, extra possibility
        float sum, max = 20, square;
        const int iterat = 200;
        float sum1[iterat] = {0};
        float square1[iterat] = {0};
        for (int k = 1; k < iterat; k++) {
            sum = 0;
            square = 0;
            for (int i = 0; i < max; i++) {
                square += start_initialization(field, i, k);
                sum += machine(field, 50, 50, i);
            }
            sum1[k] = sum / max;
            square1[k] = square / max / 2500;
            std::cout << k << '\n';
        }
        for (int i = 0; i < iterat; i++) {
            std::cout << sum1[i] << ", ";
        }
        std::cout << "\n";
        for (int i = 0; i < iterat; i++) {
            std::cout << square1[i] << ", ";
        }
    } else {
        int x[1000] = {0};
        int y[1000] = {0};
        int size = 1000;
        float summary;
        for (int i = 5; i < size; i++) {
            summary = 0;
            for (int j = 0; j < 20; j++) {
                summary += machine2(x, y, i);
            }
            std::cout << summary / 20 << ", ";
            if (i % 10 == 0) {
                std::cout << '\n';
            }
        }
    }
    return 0;
}
