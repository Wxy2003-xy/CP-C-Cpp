#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == 0) {
            return 0;
        }
        int a = abs(dividend);
        int b = abs(divisor);
        int upper, lower;
        for (int i = 0; i < 32; i++) {
            if ((a << 1) & 0x80000000) {
                upper = i;
                lower = i - 1;
                break;
            }
        }
        int lower_bound = a >> lower;
        for (int i = lower + 1; i < upper; i++) {
            lower_bound += 
        }
        if ((dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0)) {

        } else {

        }
    }
};