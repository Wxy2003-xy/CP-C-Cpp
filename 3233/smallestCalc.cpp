#include<bits/stdc++.h>

using namespace std;

/*
Given three integers and the arithmetic operators, 
determine the smallest non-negative integer possible without changing the order of the initial integers. 
Order of the operators is without their normal precedence, just left-to-right. 
Note: integer division is fine only if the remainder is zero. For example,

Given three integers, determine the smallest non-negative result that can
be computed by placement of the given operators between the numbers.
The operators may only be placed between numbers, not in front (they are not unary operators).
An operator must be placed between each pair of numbers, numbers cannot be concatenated.
*/

int op(int a, int b, int o) {
    if (o == 0) {
        return a + b;
    }
    if (o == 1) {
        if (b > a) {
            return 10000000;
        }
        return a - b;
    }
    if (o == 2) {
        return a * b;
    }
    if (o == 3) {
        if (a % b == 0 || b == 0) {
            return a / b;
        } else{
            return 10000000;
        }
    }
    return 1000000;
}

int brute_force(int a, int b, int c) {
    int ans = 10000000;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ans = min(ans, min(op(op(a, b, i), c, j), op(a, op(b, c, i), j)));
        }
    }
    return ans;
}

int main(){
    int a, b, c;
    cin>>a>>b>>c;
    cout<<brute_force(a, b, c);
}