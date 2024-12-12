#include<iostream>
using namespace std;

int offset(int n, int row, int col) {
    int res = row + col + 1;
    if (res > n) {
        return res - n;
    } else {
        return res;
    }
}

int main() {
    int n, i, j;
    cin >> n;
    if ((n - 1) / 2 % 2 == 0) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cout << offset(n, i, j);
            cout << " ";
        }
        cout << "" << endl;
    }
}