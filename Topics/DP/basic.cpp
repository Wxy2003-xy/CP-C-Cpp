#include<bits/stdc++.h>
using namespace std;
class Solution {
public:

    int fibrec(int n) {
        if (n == 0) {
            return 0;
        }
        if (n == 1 || n == 2) {
            return 1;
        }
        return fibrec(n - 1) + fibrec(n - 2);
    }
    int prev1 = 1;
    int prev2 = 0;
    int fibiter(int n) {
        int ans;
        if (n<=1) {
            return n;
        }
        for (int i = 2; i <= n; i++) {
            ans = prev1 + prev2;
            prev2 = prev1;
            prev1 = ans;
        }
        return ans;
    }
};
int main() {
    Solution s;
    for (int i = 1; i < 10; i++) {
        cout<<s.fibiter(i)<<endl;
    }
}   