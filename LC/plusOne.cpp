#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> res = digits;
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] < 9) {
                res[i] += 1;
                return res;
            } 
            else {
                res[i] = 0;
            }
        }
        vector<int> withCarry = {1};
        for (auto d : res) {
            withCarry.push_back(d);
        }
        return withCarry;
    }
};

void print_vec(vector<int> v) {
    for (auto d : v) {
        cout << d;
    }
    cout<<endl;
}

int main() {
    Solution sol;
    vector<int> a = {1};
    vector<int> b = {9,9};
    vector<int> c = {1,9};
    
    print_vec(sol.plusOne(a));
    print_vec(sol.plusOne(b));
    print_vec(sol.plusOne(c));




}