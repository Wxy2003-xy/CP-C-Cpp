#include <bits/stdc++.h>
using namespace std;

long long combination(int total, int pick) {
    if (total < pick || total == 0 || pick == 0) {
        return 0;
    }
    if (total == 1 || total == pick) {
        return 1;
    }
    if (pick == 1) {
        return total;
    }
    long long total_long = static_cast<long long>(total);
    long long pick_long = static_cast<long long>(pick);
    return combination(total - 1, pick) + combination(total - 1, pick - 1);
}

int main() {
    int x, y;
    cin>>x>>y;
    cout<< combination(x, y) <<endl;
}