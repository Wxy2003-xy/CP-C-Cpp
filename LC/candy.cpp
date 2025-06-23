#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        int len = ratings.size();
        if (len < 2) {
            return 1;
        }
        if (len == 2 && ratings[0] == ratings[1]) {
            return 2;
        }
        if (len == 2) {
            return 3;
        }
        vector<int> forward(len, 1);
        vector<int> backward(len, 1);
        for (int i = 0; i < len - 1; i++) {
            if (ratings[i] < ratings[i+1]) {
                forward[i+1] = forward[i] + 1;
            }
        }

        for (int i = len - 1; i > 0; i--) {
            if (ratings[i] < ratings[i-1]) {
                backward[i-1] = backward[i] + 1;
            }
        }

        int res = 0;
        for (int i = 0; i < len; i++) {
            res += max(forward[i], backward[i]);
        }
        return res;
    }
};

int main() {
    Solution sol;
    vector<int> v = {60, 80, 100, 100, 100, 100, 100};
    vector<int> v2 = {1,0,2};
    vector<int> v3 = {1,2,2};

    cout<<sol.candy(v)<<endl;
    cout<<sol.candy(v2)<<endl;
    cout<<sol.candy(v3)<<endl;

}