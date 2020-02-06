/*
Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:

The root is the maximum number in the array.
The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
Construct the maximum tree by the given array and output the root node of this tree.

Example 1:
Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:

      6
    /   \
   3     5
    \    / 
     2  0   
       \
        1
Note:
The size of the given array will be in the range [1,1000].
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {  //O(N)
   public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        int n = nums.size();
        stack<TreeNode*> st;

        for (int i = 0; i < n; i++) {
            TreeNode* curr = new TreeNode(nums[i]);

            while (!st.empty() && st.top()->val < nums[i]) {
                curr->left = st.top();
                st.pop();
            }

            if (!st.empty())
                st.top()->right = curr;
            st.push(curr);
        }
        while (st.size() > 1) st.pop();
        return st.top();
    }
};

int main() {
    return 0;
}
