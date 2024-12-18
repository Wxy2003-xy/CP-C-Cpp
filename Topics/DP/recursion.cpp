#include<iostream> 
#include<vector>
#include<cstring>
#include<chrono>
using namespace std; 
using namespace chrono;
class Knapsack {
  public:
    int size;
    vector<int> weights;
    vector<int> values;
    int capacity;
    int dp[1000][1000];
    void initialize() {
        memset(dp, -1, sizeof dp);  // This works because dp is an integer array
    }
    // weights.size() == values.size() == size;
    Knapsack(int n, vector<int> w, vector<int> v) {
      this->size = n;
      this->weights = w;
      this->values = v;
    }
    int naiveMax(int current, int capacity) { // current is one-indexed
      if (current == 0) {
        return 0;
      }
      if (weights[current - 1] > capacity) {
        return naiveMax(current - 1, capacity);
      }
      return max(naiveMax(current - 1, capacity),
                 naiveMax(current - 1, capacity - weights[current - 1]) + values[current - 1]);
    }

    int memoMax(int current, int capacity) {
        // Ensure dp is initialized only once
        if (dp[current][capacity] != -1) {
            return dp[current][capacity];
        }
        if (current == 0) {
            return 0;
        }
        if (weights[current - 1] > capacity) {
            return dp[current][capacity] = memoMax(current - 1, capacity);
        }
        return dp[current][capacity] = max(memoMax(current - 1, capacity),
                                          values[current - 1] + memoMax(current - 1, capacity - weights[current - 1]));
    }

};
int main() {
  vector<int> weights = {9, 12, 7, 5, 14, 10, 8, 6, 4, 3, 11, 13};
  vector<int> values = {45, 50, 35, 25, 60, 55, 40, 30, 20, 15, 48, 52};
  int size = weights.size();
  int capacity = 40;
  Knapsack* k = new Knapsack(size, weights, values);
  k->initialize();
  auto start_naive = high_resolution_clock::now(); // Start time
  cout << k->naiveMax(size, capacity) << endl;
  auto end_naive = high_resolution_clock::now(); // Start time
  auto duration_naive = duration_cast<milliseconds>(end_naive - start_naive);
  cout << "Time taken by naiveMax: " << duration_naive.count() << " ms" << endl;
  cout << "==========end========"<<endl;
  auto start_memo = high_resolution_clock::now(); // Start time
  cout << k->memoMax(size, capacity) << endl;
  auto end_memo = high_resolution_clock::now();   // End time
  auto duration_memo = duration_cast<milliseconds>(end_memo - start_memo);
  cout << "Time taken by memoMax: " << duration_memo.count() << " ms" << endl;
  return 0;
} 
