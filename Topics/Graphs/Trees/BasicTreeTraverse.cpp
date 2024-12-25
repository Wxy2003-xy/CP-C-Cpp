#include<bits/stdc++.h>
using namespace std;


// Definition for a binary tree node.
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution {
public:
    void visit(TreeNode* node, vector<int>& result) {
        result.push_back(node->val);
    }
    void preorderTraversal(TreeNode* root, vector<int>& result) {
        if (!root) {
            return ;
        }
        visit(root, result);
        if (root->left) {
            preorderTraversal(root->left, result);
        }
        if (root->right) {
            preorderTraversal(root->right, result);
        }
    }
    void inorderTraversal(TreeNode* root, vector<int>& result) {
        if (!root) {
            return ;
        }
        if (root->left) {
            inorderTraversal(root->left, result);
        }
        visit(root, result);
        if (root->right) {
            inorderTraversal(root->right, result);
        }
    }
    void postorderTraversal(TreeNode* root, vector<int>& result) {
        if (!root) {
            return ;
        }
        if (root->left) {
            postorderTraversal(root->left, result);
        }
        if (root->right) {
            postorderTraversal(root->right, result);
        }
        visit(root, result);
    }

    void levelorderTraversal(TreeNode* root, vector<int>& result, int level) {
        if (!root) {
            return ;
        }
        visit(root, result);


    }
    void populateMap(TreeNode* root, int level, unordered_map<int, vector<int>>& map) {
        if (!root) {return;}
        if (map.find(level) != map.end()) {
            map.at(level).push_back(root->val);
        } else {
            map.insert({level, vector<int>()});
            map.at(level).push_back(root->val);
        }
        if (root->left) {
            populateMap(root->left, level + 1, map);
        }
        if (root->right) {
            populateMap(root->right, level + 1, map);
        }
    }
    vector<int> largestValuesWithMap(TreeNode* root) {
        unordered_map<int, vector<int>> map;
        populateMap(root, 0, map);
        vector<int> res(map.size(), INT_MIN);
        for (const auto& [key, value] : map) {
            vector<int> v = map.at(key);
            for (int i = 0; i < v.size(); i++) {
                res[key] = max(res[key], v[i]);
            }
        }
        return res;
    }
    void level_order_traverse_max(TreeNode* root, int level, vector<int>& result) {
        if (!root) {return;}
        if (result.size() <= level) { // no guarantee level always increases, 
        // only resize when needed otherwise vector may shrink and truncate previous results
            result.resize(level + 1, INT_MIN);
        }
        result[level] = max(result[level], root->val);
        level_order_traverse_max(root->left, level + 1, result);
        level_order_traverse_max(root->right, level + 1, result);
    }
    vector<int> largestValues(TreeNode* root) {
        vector<int> result;
        level_order_traverse_max(root, 0, result);
        return result;
    }

};

int main() {

}