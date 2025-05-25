#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool match(char a, char b) {
        int aa = (int)a;
        int bb = (int)b;
        return (bb - aa == 1) || (bb - aa == 2);
    }
    bool isValid(string s) {
        if (s.length() < 2 || s.length() % 2 != 0) {
            return false;
        }
        stack<char> stk;
        stk.push(s[0]);
        for (int i = 1; i < s.length(); i++) {
            char c = s[i];
            if (stk.empty()) {
                stk.push(c);
            } else {
                char t = stk.top();
                if (match(t, c)) {
                    stk.pop();
                } else {
                    stk.push(c);
                }
            }
        }
        return stk.empty();
    }
};

int main() {
    string s = "()[]{}";
    Solution sol;
    cout<<sol.isValid(s)<<endl;
}