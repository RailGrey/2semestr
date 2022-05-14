#include <iostream>

int search(int *vert, int *hor, int l, int goal_x, int goal_y) {
    for (int i = 0; i < l; i++) {
        if ((vert[i] == goal_x) && (hor[i] == goal_y)) {
            return i;
        }
    }
    return -2;
}

int Chess(int *vert, int *hor, int l, int x, int y, int accum) {
    if (y == 7) {
        accum++;
        return accum;
    }

    int i = search(vert, hor, l, x, y+1);
    if (i == -2) {
        accum = Chess(vert, hor, l, x, y+1, accum);
    }

    i = search(vert, hor, l, x+1, y+1);
    if (i != -2) {
        accum = Chess(vert, hor, l, x+1, y+1, accum);
    }

    i = search(vert, hor, l, x-1, y+1);
    if (i != -2) {
        accum = Chess(vert, hor, l, x-1, y+1, accum);
    }

    return accum;
}

int main() {
    int n;
    std::cin >> n;
    char *pawns = new char[n*2];
    for (int i = 0; i < n*2; i++) {
        std::cin >> pawns[i];
    }
    int *verticals = new int[n];
    int *horizontals = new int[n];
    for (int i = 0; i < n; i++) {
        verticals[i] = int(pawns[i*2]) - 97;
        horizontals[i] = int(pawns[i*2+1]) - 49;
    }
    char my_pawn[2];
    std::cin >> my_pawn[0] >> my_pawn[1];
    delete []pawns;
    int accum = 0;
    std::cout << Chess(verticals, horizontals, n, int(my_pawn[0])-97, int(my_pawn[1])-49, accum);
    delete []verticals;
    delete []horizontals;
    return 0;
}

