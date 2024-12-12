#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public: 
        int trap(vector<int>& height) {
            int len = height.size();
            int max = 0;
            for (int i = 0; i < len; i++) {
                if (height[i] > max) {
                    max = height[i];
                }
            }
            for (int i = 0; i < max; i++) {
                
            }
        }
};

int main() {
    Solution solution;
    std::vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int result = solution.trap(height);
    std::cout << "Maximum height: " << result << std::endl;
    return 0;
}