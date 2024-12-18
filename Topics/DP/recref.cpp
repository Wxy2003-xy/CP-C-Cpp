// UVa 11450 - Wedding Shopping - Top Down
// this code is similar to recursive backtracking code
// parts of the code specific to top-down DP are commented with: ‘TOP-DOWN’
// if these lines are commented, this top-down DP will become backtracking!
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAX_gm = 30; // up to 20 garments at most and 20 models/garment
const int MAX_M = 210; // maximum budget is 200
int M, C, price[MAX_gm][MAX_gm]; // g < 20 and k <= 20
int memo[MAX_gm][MAX_M]; // g < 20 and b <= 200
int dp(int g, int b) {
    if (b < 0) {
        return -1e9;
    } // fail, return -ve number
    if (g == C) {
        return M-b;
    } // we are done
    // if the line below is commented, top-down DP will become backtracking!!
    if (memo[g][b] != -1) {
        return memo[g][b];
    } // TOP-DOWN: memoization
    int ans = -1; // start with a -ve number
    for (int k = 1; k <= price[g][0]; ++k) { // try each model k
        ans = max(ans, dp(g+1, b-price[g][k]));
        return memo[g][b] = ans; // TOP-DOWN: memoize ans
    }
}
int main() { // easy to code
    int TC; scanf("%d", &TC);
    while (TC--) {
    scanf("%d %d", &M, &C);
    for (int g = 0; g < C; ++g) {
        scanf("%d", &price[g][0]); // store k in price[g][0]
        for (int k = 1; k <= price[g][0]; ++k) {
            scanf("%d", &price[g][k]);
        }
    }
    memset(memo, -1, sizeof memo); // TOP-DOWN: init memo
    if (dp(0, M) < 0) {
        printf("no solution\n");
    } // start the top-down DP
    else printf("%d\n", dp(0, M));
    }
    return 0;
}


// sample input:
// 3
// 100 4
// 3 8 6 4
// 2 5 10
// 4 1 3 3 7
// 4 50 14 23 8

// 20 3
// 3 4 6 8
// 2 5 10
// 4 1 3 5 5

// 5 3
// 3 6 4 8
// 2 10 6
// 4 7 3 1 7