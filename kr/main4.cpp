#include <iostream>
using std::cout;
using std::endl;

const unsigned int N = 5;
const int left[N]  = {5, 4, 3, 2, 1}; // command code 1
const int right[N] = {1, 2, 3, 4, 5}; // command code 2
const int back[N]  = {1, 1, 1, 1, 1}; // command code 3
const int meow[N]  = {3, 2, 3, 2, 5}; // command code 4

void print(int array[N]) {
    for (int i = 0; i < N; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int is_command(int array[N]) {
    int l = 0, r = 0, b = 0, m = 0;
    for (unsigned i = 0; i < N; i++) {
        if (array[i] == left[i]) {
            l++;
        }
        if (array[i] == right[i]) {
            r++;
        }
        if (array[i] == back[i]) {
            b++;
        }
        if (array[i] == meow[i]) {
            m++;
        }
    }
    if (l == N) {
        return 1;
    } else if (r == N) {
        return 2;
    } else if (b == N) {
        return 3;
    } else if (m == N) {
        return 4;
    } else {
        return 0;
    }
}

void fill_array(int array[N], int* start) {
    for (unsigned i = 0; i < N; i++) {
        array[i] = *(start + i);
    }
}

void recognize(int* data_start, int* data_end, int* command, int** frame) {
    int array[N];
    int *c = new int;
    bool flag = true;
    if ((data_end - data_start) < N) {
        *command = 0;
        delete c;
        return;
    }
    for (int i = 0; (i < (data_end - data_start- N + 1)) && flag; i++) {
        fill_array(array, data_start + i);
        *c = is_command(array);
        if (*c != 0) {
            flag = false;
            *frame = (data_start + i);
        }
    }
    *command = *c;
    delete c;
}


int main()
{
    const int L = 21;
    int mindstream[L] = {3, 2, 3, 2, 5, 2, 3, 8, 3, 2, 1, 1, 1,
                         1, 1, 1, 1, 2, 3, 4, 5};
    int command = -1;
    int* frame = mindstream;
    int* end = mindstream + L;
    while (command)
    {
        recognize(frame, end, &command, &frame);
        if (!command) break;
        switch(command)
        {
            case 1:
                cout << "left ";
                break;
            case 2:
                cout << "right ";
                break;
            case 3:
                cout << "back ";
                break;
            case 4:
                cout << "MEOOOOW ";
                break;
        }
        frame += N;
    }
    cout << endl;
    return 0;
}