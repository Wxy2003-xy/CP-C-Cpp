#include<bits/stdc++.h>

using namespace std;
using namespace chrono;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        
    }
    int combination(vector<int>& coins, int curr, int sum) {
        
    }
    int helper(int c, int curr, int sum) {
        if (c + curr > sum) {
            return 0;
        }
        return helper(c, curr - c, sum) + helper(c, curr, )
    }
    void enumerate_coint_change(vector<int>& coins, int amount, vector<vector<int>>& enumeration) {

    }
};

int main() {

}