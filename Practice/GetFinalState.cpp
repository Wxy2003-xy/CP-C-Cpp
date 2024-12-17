#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    struct Pair {
        int value;
        int index;
        bool operator<(const Pair& other) const {
            if (this->value == other.value) {
                return this->index > other.index;
            }
            return this->value > other.value;
        }
    };
    vector<int> static getFinalStateNaive(vector<int>& nums, int k, int multiplier) {
        priority_queue<Pair> pq;
        for (int i = 0; i < nums.size(); i++) {
            pq.push({nums.at(i), i});
        }
        for (int i = 0; i < k; i++) {
            Pair min = pq.top();
            pq.pop();
            min.value *= multiplier;
            pq.push(min);
        }
        vector<int> res(nums.size());
        while (!pq.empty()) {
            Pair i = pq.top();
            pq.pop();
            res[i.index] = i.value;
        }
        return res;
    }
        vector<int> static getFinalState(vector<int>& nums, int k, int multiplier) {
        priority_queue<Pair> pq;
        for (int i = 0; i < nums.size(); i++) {
            pq.push({nums.at(i), i});
        }
        for (int i = 0; i < k; i++) {
            Pair min = pq.top();
            pq.pop();
            min.value *= multiplier;
            pq.push(min);
        }
        vector<int> res(nums.size());
        while (!pq.empty()) {
            Pair i = pq.top();
            pq.pop();
            res[i.index] = i.value;
        }
        return res;
    }
};


int main() {
    vector<int> t = {2,1,3,5,6};
    vector<int> r = Solution::getFinalState(t, 5, 2);
    for (int i = 0; i < r.size(); i++) {
        cout << r[i] << endl;
    }
    return 0;
}