#include<iostream>
#include<vector>
#include<math.h>
#include<sstream>
using namespace std;

bool isSqure(int x) {
    long long sr = sqrt(x);
    return (x % 2 != 0 && sr * sr == x);
}

int main() {
    int t; 
    cin >> t;

    while (t--) { 
        int n; 
        cin >> n;
        int tmp;
        int sum = 0;
        int count = 0;
        for (int i = 0; i < n; i++) {
            cin >> tmp;
            sum += tmp;
            if (isSqure(tmp)) {
                count++;
            }
        }
        cout << count << endl;
    }

    return 0;
}