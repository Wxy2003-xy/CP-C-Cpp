#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            bool d[9] = {0,0,0,0,0,0,0,0,0};
            for (int j = 0; j < 9; j++) {
                char c = board[i][j];
                if (c == '.') {
                    continue;
                }
                if (d[(int)c - 49]) {
                    return false;
                } else {
                    d[(int)c - 49] = 1;
                }
            }
        }
        for (int i = 0; i < 9; i++) {
            bool d[9] = {0,0,0,0,0,0,0,0,0};
            for (int j = 0; j < 9; j++) {
                char c = board[j][i];
                if (c == '.') {
                    continue;
                }
                if (d[(int)c - 49]) {
                    return false;
                } else {
                    d[(int)c - 49] = 1;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                bool d[9] = {0,0,0,0,0,0,0,0,0};
                for (int k = 0; k < 3; k++) {
                    for (int h = 0; h < 3; h++) {
                        char c = board[3*i+k][3*j+h];
                        if (c == '.') {
                            continue;
                        }
                        if (d[(int)c - 49]) {
                            return false;
                        } else {
                            d[(int)c - 49] = 1;
                        }
                    }
                }
            }
        }
        return true;
    }
};