#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string s;
        if (strs.size() == 0) {
            return s; 
        }
        if (strs.size() == 1) {
            return strs[0];
        }
        int shortest = INT_MAX;
        for (int i = 0; i < strs.size(); i++) {
            shortest = min(shortest, (int)strs[i].length());
        }
        for (int i = 0; i < shortest; i++) {
            char c = strs[0][i];
            for (int j = 1; j < strs.size(); j++) {
                if (strs[j][i] != c) {
                    return s;
                } 
            }
            s.push_back(c);
        }
        return s;
    }
};

int main() {
    std::vector<std::string> words = { "flower", "flow", "flight" };
    std::vector<std::string> words2 = { "dog","racecar","car" };

    Solution sol;
    cout<<sol.longestCommonPrefix(words)<<endl;
    cout<<sol.longestCommonPrefix(words2)<<endl;

}