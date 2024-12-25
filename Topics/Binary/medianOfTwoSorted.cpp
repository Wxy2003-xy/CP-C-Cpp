#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    double findMedianSortedArraysNaive(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size();
        int len2 = nums2.size();
        // if (len1 == 0) {
        //     if (len2 % 2 !=0) {
        //         return static_cast<double>(nums2[floor(len2/2.0)]);
        //     } else {
        //         return (static_cast<double>(nums2[floor(len2/2.0)])
        //         + static_cast<double>(nums2[ceil(len2/2.0)]) )/2;
        //     }
        // }
        // if (len2 == 0) {
        //     if (len1 % 2 !=0) {
        //         return static_cast<double>(nums1[floor(len1/2.0)]);
        //     } else {
        //         return (static_cast<double>(nums1[floor(len1/2.0)])
        //         + static_cast<double>(nums1[ceil(len1/2.0)]) )/2;
        //     }
        // }
        int ptr1 = 0;
        int ptr2 = 0;
        int len = len1 + len2;
        int a[len1 + len2]; 
        for (int i = 0; i < len1 + len2; i++) {
            if (ptr1 == len1) {
                a[i] = nums2.at(ptr2);
                ptr2++;
            }
            else if (ptr2 == len2) {
                a[i] = nums1.at(ptr1);
                ptr1++;
            }
            else if (nums1.at(ptr1)<=nums2.at(ptr2)) {
                a[i] = nums1.at(ptr1);
                ptr1++;
            } else {
                a[i] = nums2.at(ptr2);
                ptr2++;
            }
        }
        for (int i = 0 ; i < len; i++) {
            cout<<a[i]<<" ";
        }
        cout<<endl;
        if (len % 2 == 0) {
            int medl = len / 2 - 1;
            int medh = len / 2;
            return ((a[medl] + a[medh]) / 2.0);
        }
        return a[len/2];
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size();
        int len2 = nums2.size();
        int shorter = min(len1, len2);
        int longer = max(len1, len2);
        int total_length = len1 + len2;
        int first_half;
        if (total_length % 2 != 0) {
            first_half = total_length / 2.0;
        } else {
            first_half = total_length / 2.0 - 1;
        }

        int mid1 = floor(len1 / 2.0);
        return 0;
    }

    double helper(vector<int>& a, vector<int>& b, int end_idx, int shorter, int half) {
        int from1 = end_idx + 1;
        return 0; //TODO

    }

    bool search(vector<int>& a, int b) {
        int last = a.size() - 1;
        return binary_search(a, 0, last, b);
    }
    bool binary_search(vector<int>& a, int start, int end, int b) {
        if (start > end) {
            return false;
        }
        int mid = start + (end - start) / 2;
        if (a[mid] == b) {
            return true;
        }
        if (a[mid] < b) {
            return binary_search(a, mid+1, end, b);
        }
        if (a[mid] > b) {
            return binary_search(a, start, mid-1, b);
        }
        return false;
    }
};

int main() {
    Solution s;
    vector<int> n1 = {1,4,6,7};
    vector<int> n2 = {2,3,8,9};
    vector<int> n3 = {1,2,3,4};
    vector<int> n4 = {6,7,8,9};
    vector<int> n5 = {1,2};
    vector<int> n6 = {3,4};
    vector<int> nn = {1,2,3,4,5,6,7,8,10,11};
    // cout<<s.findMedianSortedArrays(n5, n6);
    cout << (s.search(nn, 5) ? "Found" : "Not Found") << endl; // Output: Found
    cout << (s.search(nn, 9) ? "Found" : "Not Found") << endl; // Output: Not Found

}