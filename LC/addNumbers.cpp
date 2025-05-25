#include<bits/stdc++.h>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return helper(l1, l2, 0);
    }

    ListNode* helper(ListNode* l1, ListNode* l2, int carry) {
        if (!l1 && !l2 && carry == 0) {
            return nullptr;
        }
        int x = l1?l1->val:0;
        int y = l2?l2->val:0;
        int presum = x + y + carry;
        int new_carry = presum / 10;
        int sum = presum % 10;
        ListNode* node = new ListNode(sum);
        node->next = helper(l1?l1->next:nullptr, l2?l2->next:nullptr, new_carry);
        return node;
    }
};