#include<bits/stdc++.h>
using namespace std;
int main() {
    int c;
    cin >> c;
    for (int i = 0; i < c; i++) {
        int n, x, y;
        cin >> n >> y;
        x = y;
        if (n == 0) {
            cout << endl;
            continue;
        }
        if (n == 1) {
            cout << y << endl;
            continue;
        }
        if (y % 2 == 0) {
            cout << y << " ";
            for (int i = 1; i < n; i++) {
                cout << 0 << " ";
            }
            cout << endl;
            continue;
        }
        int a = 0;
        int b = 0;
        bool one = false;
        int counter = 0;
        while (x > 0) {
            if (x & 1 == 1 && !one) {
                a+=1;
                x = x >> 1;
                counter +=1;
                continue;
            } 
            if (x & 1 == 0 && x > 0 && !one) {
                one = true;
                counter+=1;
                x = x >> 1;
                continue;
            }
            if (one && x & 1 == 1) {
                counter+=1;
                b = counter;
                break;
            } else {
                x = x >> 1;
                counter+=1;
                continue;
            }
        }

        if (b == 0 && !one) {
            b = counter - 1;
        }
        uint32_t mask = ~((1ULL << b) - 1);
        int m = y & mask;
        int cn = pow(2, a);
        int j;
        cout << "--" << cn << ", " << n  << ", " << a << "---" <<endl;
        cout << m << " ";
        for (j = 1; j < min(cn, n); j++) {
            cout << j - 1 << " ";
        }
        for (int k = j; k < n; k++) {
            cout << 0 << " ";
        }
        cout << endl;
    }
}
