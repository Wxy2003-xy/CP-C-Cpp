#include<bits/stdc++.h>
using namespace std;
vector<vector<int>> combination(vector<int>& _gpa, int sum) {
    if (sum < 2) {return {};}
    vector<vector<vector<int>>> dp(sum + 1);
    dp[0].push_back({});
    for (int i = 0; i < sum + 1; i++) {
        
    }
    return dp[sum];
}
int main() {
    vector<int> _gpa = {10, 9, 8, 7, 6, 5, 4, 3, 2}; 
    int gpa = 1.2;
    int mod = 5;
    vector<vector<int>> comb = combination(_gpa, 6);
    for (int i = 0; i < comb.size(); i++) {
        for (int j = 0; j < comb[i].size(); j++) {
            cout<<comb[i][j]<<" ";
        }
        cout<<endl;
    }
}