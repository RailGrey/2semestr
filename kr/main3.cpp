#include <iostream>


int * compress(int ** matrix, int n, int m) {
    int tmp, idx = 0;
    int *array = new int[n*m];
    bool flag = false;
    for (int i = 0; i < n; i++) {
        tmp = 0;
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] != 0) {
                tmp++;
                if (tmp > 3) {
                    flag = true;
                }
                array[idx] = matrix[i][j];
                idx++;
            }
        }
        if (tmp < 3) {
            flag = true;
        }
    }
    int *result = new int[idx];
    for (int i = 0; i < idx; i++) {
        result[i] = array[i];
    }
    delete []array;
    for (int i = 0; i < n; i++)
    {
        delete [] matrix[i];
    }
    delete [] matrix;
    if (flag) {
        delete []result;
        return nullptr;
    } else {
        return result;
    }
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    int** a = new int*[n];
    for (int i = 0; i < n; i++)
        a[i] = new int[m];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            std::cin >> a[i][j];

    int* compressed = compress(a, n, m);

    if (!compressed) return 0;

    for (int i = 0; i < n * 3; i++)
        std::cout << compressed[i] << " ";
    std::cout << std::endl;

    delete[] compressed;
    return 0;
}

