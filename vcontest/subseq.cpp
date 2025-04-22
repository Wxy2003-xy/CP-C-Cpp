#include<bits/stdc++.h>
using namespace std;
int main() {
    int c;
    cin >> c;
    for (int i = 0; i < c; i++) {
        int l;
        cin >> l;
        string s;
        cin >> ws;
        getline(cin, s);
        int d = 0;
        int u = 0;
        for (int j = 0; j < l; j++) {
            if (s[j] == '-') {
                d += 1;
            } else if (s[j] == '_') {
                u += 1;
            }
        }
        if (u < 1 || d < 2) {
            cout << 0 << endl;
        } else {
            int64_t f, e;
            f = d / 2;
            e = d - f;
            cout << f * e * u << endl;
        }
    }
}