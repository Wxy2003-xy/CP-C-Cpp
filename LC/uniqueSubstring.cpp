#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.length() < 2) {
            return s.length();
        }
        int maxlen = 1;
        int i = 0;
        unordered_map<char, int> map;
        map.insert({s[0], 0});
        for (int j = 1; j < s.length(); j++) {
            if (map.count(s[j]) > 0 && i <= map.find(s[j])->second) {
                i = map[s[j]] + 1;
                map[s[j]] = j;
            } else if (map.count(s[j]) > 0) {
                map[s[j]] = j;
                maxlen = max(j - i + 1, maxlen);
            } else {
                map.insert({s[j], j});
                maxlen = max(j - i + 1, maxlen);
            }

        }
        return maxlen;
    }
};

int main() {
    Solution sol;
    string s = "tmmzuxt";
    string s0 = "pwwkew";
    string s1 = "au";
    string s2 = "aabaab!bb";
    cout<<"start"<<endl;

    cout << sol.lengthOfLongestSubstring(s) << endl;
    cout << sol.lengthOfLongestSubstring(s0) << endl;
    cout << sol.lengthOfLongestSubstring(s1) << endl;
    cout << sol.lengthOfLongestSubstring(s2) << endl;
}