#include<bits/stdc++.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}


};
    // Utility function to create a list from a vector
    ListNode* createList(const vector<int>& nums) {
        ListNode* head = new ListNode();
        ListNode* curr = head;
        for (int num : nums) {
            curr->next = new ListNode(num);
            curr = curr->next;
        }
        return head->next;
    }
// Utility function to print the list
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int k = lists.size();
        if (k < 1) {
            return new ListNode();
        }
        vector<int> ptrs(k, 0);
        return merge(lists, k);
    }

    ListNode* merge(vector<ListNode*>& lists, int k) {
        int c = 0;
        for (int i = 0; i < k; i++) {
            if (lists[c]->val > lists[i]->val) {
                c = i;
            }
        }
        int v = lists[c]->val;
        lists[c] = lists[c]->next;
        return new ListNode(v, merge(lists, k));
    }
};

int main() {
Solution solution;

    // Test Case 1
    vector<ListNode*> lists1 = {
        createList({1, 4, 5}),
        createList({1, 3, 4}),
        createList({2, 6})
    };
    ListNode* result1 = solution.mergeKLists(lists1);
    cout << "Merged List 1: ";
    printList(result1);

    // Test Case 2 (Empty list)
    vector<ListNode*> lists2 = {};
    ListNode* result2 = solution.mergeKLists(lists2);
    cout << "Merged List 2: ";
    printList(result2);  // Should output nothing (empty list)

    // Test Case 3 (Single list)
    vector<ListNode*> lists3 = {
        createList({1, 2, 3, 4, 5})
    };
    ListNode* result3 = solution.mergeKLists(lists3);
    cout << "Merged List 3: ";
    printList(result3);

    // Test Case 4 (Lists with different lengths)
    vector<ListNode*> lists4 = {
        createList({1, 3}),
        createList({2, 4, 6}),
        createList({0, 5})
    };
    ListNode* result4 = solution.mergeKLists(lists4);
    cout << "Merged List 4: ";
    printList(result4);

    return 0;
}