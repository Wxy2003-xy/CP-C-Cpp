#include<iostream>
#include<queue>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    static long long pickGifts(vector<int>& gifts, int k) {
        priority_queue<int> pq;
        int i;
        for (i = 0; i < gifts.size(); i++) {
            pq.push(gifts[i]);
        }

        for (i = 0; i < k; i++) {
            long long take = pq.top();
            pq.pop();
            take = sqrt(take);
            pq.push(take);
        }
        long long sum = 0;
        while (!pq.empty()) {
            sum += pq.top();
            pq.pop();
        }
        return sum;
    }
};

int main() {
    vector<int> a = {25, 64, 9, 4, 100};
    int x = Solution::pickGifts(a, 4);
    std::cout << x << std::endl;
    return 0;
}