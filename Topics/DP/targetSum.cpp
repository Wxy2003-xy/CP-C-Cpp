#include<bits/stdc++.h>

using namespace std;
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        return helper(nums, target, sum);
    }
    int helper(vector<int>& a, int t, int sum) {
        int len = a.size();
        if (len == 0) {return 0;}
        if (len == 1) {return a[0] == t ? 1 : 0;}
        if (t > sum) {return 0;}
        a.resize(len - 1);
        cout<<"re"<<endl;
        return helper(a, t - a[len - 1], sum) + helper(a, t + a[len - 1], sum);
    }
};
int main() {
    vector<int> a = {1,1,1,1,1};
    int target = 3;
    Solution s;
    cout<< s.findTargetSumWays(a, target);
}