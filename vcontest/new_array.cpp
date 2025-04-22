#include<bits/stdc++.h>

using namespace std;

int main() {
    int c;
    cin >> c;
    for (int i = 0; i < c; i++) {
        int n, k, p;
        cin >> n >> k >> p;
        k = abs(k);
        int r;
        if (k % p == 0) {
            r = k / p;
        } else {
            r = k / p + 1;
        }
        if (r > n) {
            cout << -1 << endl;
        } else {
            cout << r << endl;
        }
    }
}