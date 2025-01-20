#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxScore(string s) {
        int score = 0;
        for (int i = 1; i < s.size(); i++) {
            score = max(score, split_count(s, i));
        }
        return score;
    }
    int split_count(string s, int split) {
        int sum = 0;
        for (int i = 0; i < split; i++) {
            if (s.at(i) == '0') {
                sum += 1;
            }
        }
        for (int i = split; i < s.size(); i++) {
            if (s.at(i) == '1') {
                sum += 1;
            }
        }
        return sum;
    }
};

int main() {
    string s = "01";
    Solution l;
    cout<<l.maxScore(s);
}