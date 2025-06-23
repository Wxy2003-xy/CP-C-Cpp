#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) {
            return s;
        }
        string res;
        int unit = numRows * 2 - 2;
        int curr = 0;
        set<int> t;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j <= s.length() / unit + 1; j++) {
                int left = unit * j - i;
                int right = unit * j + i;
                if (left >= 0 && left < s.length() && t.count(left) <= 0) {
                    res.push_back(s[left]);
                    t.insert(left);
                    cout << curr << ", " << left <<endl;
                    curr+=1;
                }
                if (right >= 0 && right < s.length() && t.count(right) <= 0) {
                    res.push_back(s[right]);
                    t.insert(right);
                    cout << curr << ", " << right <<endl;
                    curr+=1;
                }
            }
        }
        return res;
    }
};

int main() {
    string s = "PAYPALISHIRING";
    string v = "ABCDE";
    Solution sol;
    cout << sol.convert(v, 4) << endl;

}