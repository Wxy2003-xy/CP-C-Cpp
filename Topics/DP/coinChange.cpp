#include<bits/stdc++.h>

using namespace std;
using namespace chrono;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        
    }
    int combination(vector<int>& coins, int curr, int sum) {
        int a = 0;
        for (int i = 0; i < coins.size(); i++) {
            a += helper(coins[i], curr, sum);
        }
    }
    int helper(int c, int curr, int sum) {
        if (c + curr > sum) {
            return 0;
        } else {
        return 1 + helper(c, curr - c, sum);
        }
    }
    void enumerate_coint_change(vector<int>& coins, int amount, vector<vector<int>>& enumeration) {

    }
};

int main() {

}